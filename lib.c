/**
 * See Copyright Notice in picrin.h
 */

#include "picrin.h"
#include "picrin/lib.h"
#include "picrin/pair.h"
#include "picrin/macro.h"
#include "picrin/error.h"
#include "picrin/string.h"
#include "picrin/proc.h"

struct pic_lib *
pic_open_library(pic_state *pic, pic_value name)
{
  struct pic_lib *lib;
  struct pic_senv *senv;

  if ((lib = pic_find_library(pic, name)) != NULL) {

#if DEBUG
    printf("* reopen library: ");
    pic_debug(pic, name);
    puts("");
#endif

    return lib;
  }

  senv = pic_null_syntactic_environment(pic);

  lib = (struct pic_lib *)pic_obj_alloc(pic, sizeof(struct pic_lib), PIC_TT_LIB);
  lib->env = senv;
  lib->name = name;
  xh_init_int(&lib->exports, sizeof(pic_sym));

  /* register! */
  pic->libs = pic_acons(pic, name, pic_obj_value(lib), pic->libs);

  return lib;
}

void
pic_in_library(pic_state *pic, pic_value spec)
{
  struct pic_lib *lib;

  lib = pic_find_library(pic, spec);
  if (! lib) {
    pic_errorf(pic, "library not found: ~a", spec);
  }
  pic->lib = lib;
}

struct pic_lib *
pic_find_library(pic_state *pic, pic_value spec)
{
  pic_value v;

  v = pic_assoc(pic, spec, pic->libs, NULL);
  if (pic_false_p(v)) {
    return NULL;
  }
  return pic_lib_ptr(pic_cdr(pic, v));
}

static void
import_table(pic_state *pic, pic_value spec, xhash *imports)
{
  const pic_sym sONLY = pic_intern_cstr(pic, "only");
  const pic_sym sRENAME = pic_intern_cstr(pic, "rename");
  const pic_sym sPREFIX = pic_intern_cstr(pic, "prefix");
  const pic_sym sEXCEPT = pic_intern_cstr(pic, "except");
  struct pic_lib *lib;
  xhash table;
  pic_value val;
  pic_sym sym, id;
  xh_iter it;

  xh_init_int(&table, sizeof(pic_sym));

  if (pic_list_p(spec)) {
    if (pic_eq_p(pic_car(pic, spec), pic_sym_value(sONLY))) {
      import_table(pic, pic_cadr(pic, spec), &table);
      pic_for_each (val, pic_cddr(pic, spec)) {
        xh_put_int(imports, pic_sym(val), &xh_val(xh_get_int(&table, pic_sym(val)), pic_sym));
      }
      goto exit;
    }
    if (pic_eq_p(pic_car(pic, spec), pic_sym_value(sRENAME))) {
      import_table(pic, pic_cadr(pic, spec), imports);
      pic_for_each (val, pic_cddr(pic, spec)) {
        id = xh_val(xh_get_int(imports, pic_sym(pic_car(pic, val))), pic_sym);
        xh_del_int(imports, pic_sym(pic_car(pic, val)));
        xh_put_int(imports, pic_sym(pic_cadr(pic, val)), &id);
      }
      goto exit;
    }
    if (pic_eq_p(pic_car(pic, spec), pic_sym_value(sPREFIX))) {
      import_table(pic, pic_cadr(pic, spec), &table);
      xh_begin(&it, &table);
      while (xh_next(&it)) {
        val = pic_list_ref(pic, spec, 2);
        sym = pic_intern_str(pic, pic_format(pic, "~s~s", val, pic_sym_value(xh_key(it.e, pic_sym))));
        xh_put_int(imports, sym, &xh_val(it.e, pic_sym));
      }
      goto exit;
    }
    if (pic_eq_p(pic_car(pic, spec), pic_sym_value(sEXCEPT))) {
      import_table(pic, pic_cadr(pic, spec), imports);
      pic_for_each (val, pic_cddr(pic, spec)) {
        xh_del_int(imports, pic_sym(val));
      }
      goto exit;
    }
  }
  lib = pic_find_library(pic, spec);
  if (! lib) {
    pic_errorf(pic, "library not found: ~a", spec);
  }
  xh_begin(&it, &lib->exports);
  while (xh_next(&it)) {
    xh_put_int(imports, xh_key(it.e, pic_sym), &xh_val(it.e, pic_sym));
  }

 exit:
  xh_destroy(&table);
}

static void
import(pic_state *pic, pic_value spec)
{
  xhash imports;
  xh_iter it;

  xh_init_int(&imports, sizeof(pic_sym)); /* pic_sym to pic_sym */

  import_table(pic, spec, &imports);

  xh_begin(&it, &imports);
  while (xh_next(&it)) {

#if DEBUG
    printf("* importing %s as %s\n", pic_symbol_name(pic, xh_key(it.e, pic_sym)), pic_symbol_name(pic, xh_val(it.e, pic_sym)));
#endif

    pic_put_rename(pic, pic->lib->env, xh_key(it.e, pic_sym), xh_val(it.e, pic_sym));
  }

  xh_destroy(&imports);
}

static void
export(pic_state *pic, pic_value spec)
{
  const pic_sym sRENAME = pic_intern_cstr(pic, "rename");
  pic_value a, b;
  pic_sym rename;

  if (pic_sym_p(spec)) {        /* (export a) */
    a = b = spec;
  } else {                      /* (export (rename a b)) */
    if (! pic_list_p(spec))
      goto fail;
    if (! pic_length(pic, spec) == 3)
      goto fail;
    if (! pic_eq_p(pic_car(pic, spec), pic_sym_value(sRENAME)))
      goto fail;
    if (! pic_sym_p(a = pic_list_ref(pic, spec, 1)))
      goto fail;
    if (! pic_sym_p(b = pic_list_ref(pic, spec, 2)))
      goto fail;
  }

  if (! pic_find_rename(pic, pic->lib->env, pic_sym(a), &rename)) {
    pic_errorf(pic, "export: symbol not defined %s", pic_symbol_name(pic, pic_sym(a)));
  }

#if DEBUG
  printf("* exporting %s as %s\n", pic_symbol_name(pic, pic_sym(b)), pic_symbol_name(pic, rename));
#endif

  xh_put_int(&pic->lib->exports, pic_sym(b), &rename);

  return;

 fail:
  pic_errorf(pic, "illegal export spec: ~s", spec);
}

void
pic_import(pic_state *pic, pic_value spec)
{
  import(pic, spec);
}

void
pic_import_library(pic_state *pic, struct pic_lib *lib)
{
  import(pic, lib->name);
}

void
pic_export(pic_state *pic, pic_sym sym)
{
  export(pic, pic_sym_value(sym));
}

static bool
condexpand(pic_state *pic, pic_value clause)
{
  const pic_sym sELSE = pic_intern_cstr(pic, "else");
  const pic_sym sLIBRARY = pic_intern_cstr(pic, "library");
  const pic_sym sOR = pic_intern_cstr(pic, "or");
  const pic_sym sAND = pic_intern_cstr(pic, "and");
  const pic_sym sNOT = pic_intern_cstr(pic, "not");
  pic_sym tag;
  pic_value c, feature;

  if (pic_eq_p(clause, pic_sym_value(sELSE))) {
    return true;
  }
  if (pic_sym_p(clause)) {
    pic_for_each (feature, pic->features) {
      if(pic_eq_p(feature, clause))
        return true;
    }
    return false;
  }

  if (! (pic_pair_p(clause) && pic_sym_p(pic_car(pic, clause)))) {
    pic_errorf(pic, "invalid 'cond-expand' clause ~s", clause);
  } else {
    tag = pic_sym(pic_car(pic, clause));
  }

  if (tag == sLIBRARY) {
    return pic_find_library(pic, pic_list_ref(pic, clause, 1)) != NULL;
  }
  if (tag == sNOT) {
    return ! condexpand(pic, pic_list_ref(pic, clause, 1));
  }
  if (tag == sAND) {
    pic_for_each (c, pic_cdr(pic, clause)) {
      if (! condexpand(pic, c))
        return false;
    }
    return true;
  }
  if (tag == sOR) {
    pic_for_each (c, pic_cdr(pic, clause)) {
      if (condexpand(pic, c))
        return true;
    }
    return false;
  }

  pic_errorf(pic, "unknown 'cond-expand' directive ~s", clause);
}

static pic_value
pic_lib_condexpand(pic_state *pic)
{
  pic_value *clauses;
  size_t argc, i;

  pic_get_args(pic, "*", &argc, &clauses);

  for (i = 0; i < argc; i++) {
    if (condexpand(pic, pic_car(pic, clauses[i]))) {
      return pic_cons(pic, pic_sym_value(pic->rBEGIN), pic_cdr(pic, clauses[i]));
    }
  }

  return pic_none_value();
}

static pic_value
pic_lib_import(pic_state *pic)
{
  size_t argc, i;
  pic_value *argv;

  pic_get_args(pic, "*", &argc, &argv);

  for (i = 0; i < argc; ++i) {
    import(pic, argv[i]);
  }

  return pic_none_value();
}

static pic_value
pic_lib_export(pic_state *pic)
{
  size_t argc, i;
  pic_value *argv;

  pic_get_args(pic, "*", &argc, &argv);

  for (i = 0; i < argc; ++i) {
    export(pic, argv[i]);
  }

  return pic_none_value();
}

static pic_value
pic_lib_define_library(pic_state *pic)
{
  struct pic_lib *prev = pic->lib;
  size_t argc, i;
  pic_value spec, *argv;

  pic_get_args(pic, "o*", &spec, &argc, &argv);

  pic_open_library(pic, spec);

  pic_try {
    pic_in_library(pic, spec);

    for (i = 0; i < argc; ++i) {
      pic_void(pic_eval(pic, argv[i], pic->lib));
    }

    pic_in_library(pic, prev->name);
  }
  pic_catch {
    pic_in_library(pic, prev->name); /* restores pic->lib even if an error occurs */
    pic_throw_error(pic, pic->err);
  }

  return pic_none_value();
}

static pic_value
pic_lib_in_library(pic_state *pic)
{
  pic_value spec;

  pic_get_args(pic, "o", &spec);

  pic_in_library(pic, spec);

  return pic_none_value();
}

void
pic_init_lib(pic_state *pic)
{
  void pic_defmacro(pic_state *, pic_sym, pic_sym, pic_func_t);

  pic_defmacro(pic, pic->sCOND_EXPAND, pic->rCOND_EXPAND, pic_lib_condexpand);
  pic_defmacro(pic, pic->sIMPORT, pic->rIMPORT, pic_lib_import);
  pic_defmacro(pic, pic->sEXPORT, pic->rEXPORT, pic_lib_export);
  pic_defmacro(pic, pic->sDEFINE_LIBRARY, pic->rDEFINE_LIBRARY, pic_lib_define_library);
  pic_defmacro(pic, pic->sIN_LIBRARY, pic->rIN_LIBRARY, pic_lib_in_library);
}