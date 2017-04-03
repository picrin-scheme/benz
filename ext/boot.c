#include "picrin.h"
#include "picrin/extra.h"

static const char boot_rom[][80] = {
"((core#lambda (.define-transformer.2228 .the.2229) ((core#lambda (.the-core-defi",
"ne.2230 .the-core-lambda.2231 .the-core-begin.2232 .the-core-quote.2233 .the-cor",
"e-set!.2234 .the-core-if.2235 .the-core-define-macro.2236 .the-define.2237 .the-",
"lambda.2238 .the-begin.2239 .the-quote.2240 .the-set!.2241 .the-if.2242 .the-def",
"ine-macro.2243) (core#begin (.define-transformer.2228 (core#quote quote) (core#l",
"ambda (.form.2248 .env.2249) (core#if (= (length .form.2248) 2) (cons .the-core-",
"quote.2233 (cons (cadr .form.2248) (core#quote ()))) (error \"malformed quote\" .f",
"orm.2248)))) (core#begin (.define-transformer.2228 (core#quote if) (core#lambda ",
"(.form.2250 .env.2251) ((core#lambda (.len.2252) (core#if (= .len.2252 3) (appen",
"d .form.2250 (cons (core#quote #undefined) (core#quote ()))) (core#if (= .len.22",
"52 4) (cons .the-core-if.2235 (cdr .form.2250)) (error \"malformed if\" .form.2250",
")))) (length .form.2250)))) (core#begin (.define-transformer.2228 (core#quote be",
"gin) (core#lambda (.form.2253 .env.2254) ((core#lambda (.len.2255) (core#if (= .",
"len.2255 1) #undefined (core#if (= .len.2255 2) (cadr .form.2253) (core#if (= .l",
"en.2255 3) (cons .the-core-begin.2232 (cdr .form.2253)) (cons .the-core-begin.22",
"32 (cons (cadr .form.2253) (cons (cons .the-begin.2239 (cddr .form.2253)) (core#",
"quote ())))))))) (length .form.2253)))) (core#begin (.define-transformer.2228 (c",
"ore#quote set!) (core#lambda (.form.2256 .env.2257) (core#if (core#if (= (length",
" .form.2256) 3) (identifier? (cadr .form.2256)) #f) (cons .the-core-set!.2234 (c",
"dr .form.2256)) (error \"malformed set!\" .form.2256)))) (core#begin (core#define ",
".check-formal.2244 (core#lambda (.formal.2258) ((core#lambda (.it.2259) (core#if",
" .it.2259 .it.2259 ((core#lambda (.it.2260) (core#if .it.2260 .it.2260 ((core#la",
"mbda (.it.2261) (core#if .it.2261 .it.2261 #f)) (core#if (pair? .formal.2258) (c",
"ore#if (identifier? (car .formal.2258)) (.check-formal.2244 (cdr .formal.2258)) ",
"#f) #f)))) (identifier? .formal.2258)))) (null? .formal.2258)))) (core#begin (.d",
"efine-transformer.2228 (core#quote lambda) (core#lambda (.form.2262 .env.2263) (",
"core#if (= (length .form.2262) 1) (error \"malformed lambda\" .form.2262) (core#if",
" (.check-formal.2244 (cadr .form.2262)) (cons .the-core-lambda.2231 (cons (cadr ",
".form.2262) (cons (cons .the-begin.2239 (cddr .form.2262)) (core#quote ())))) (e",
"rror \"malformed lambda\" .form.2262))))) (core#begin (.define-transformer.2228 (c",
"ore#quote define) (core#lambda (.form.2264 .env.2265) ((core#lambda (.len.2266) ",
"(core#if (= .len.2266 1) (error \"malformed define\" .form.2264) ((core#lambda (.f",
"ormal.2267) (core#if (identifier? .formal.2267) (core#if (= .len.2266 3) (cons .",
"the-core-define.2230 (cdr .form.2264)) (error \"malformed define\" .form.2264)) (c",
"ore#if (pair? .formal.2267) (cons .the-define.2237 (cons (car .formal.2267) (con",
"s (cons .the-lambda.2238 (cons (cdr .formal.2267) (cddr .form.2264))) (core#quot",
"e ())))) (error \"define: binding to non-varaible object\" .form.2264)))) (cadr .f",
"orm.2264)))) (length .form.2264)))) (core#begin (.define-transformer.2228 (core#",
"quote define-macro) (core#lambda (.form.2268 .env.2269) (core#if (= (length .for",
"m.2268) 3) (core#if (identifier? (cadr .form.2268)) (cons .the-core-define-macro",
".2236 (cdr .form.2268)) (error \"define-macro: binding to non-variable object\" .f",
"orm.2268)) (error \"malformed define-macro\" .form.2268)))) (core#begin #undefined",
" (core#begin (.define-transformer.2228 (core#quote else) (core#lambda ._.2270 (e",
"rror \"invalid use of auxiliary syntax\" (core#quote else)))) (core#begin (.define",
"-transformer.2228 (core#quote =>) (core#lambda ._.2271 (error \"invalid use of au",
"xiliary syntax\" (core#quote =>)))) (core#begin (.define-transformer.2228 (core#q",
"uote unquote) (core#lambda ._.2272 (error \"invalid use of auxiliary syntax\" (cor",
"e#quote unquote)))) (core#begin (.define-transformer.2228 (core#quote unquote-sp",
"licing) (core#lambda ._.2273 (error \"invalid use of auxiliary syntax\" (core#quot",
"e unquote-splicing)))) (core#begin (.define-transformer.2228 (core#quote let) (c",
"ore#lambda (.form.2274 .env.2275) (core#if (identifier? (cadr .form.2274)) ((cor",
"e#lambda (.name.2276 .formal.2277 .body.2278) (cons (cons .the-lambda.2238 (cons",
" (core#quote ()) (cons (cons .the-define.2237 (cons (cons .name.2276 (map car .f",
"ormal.2277)) .body.2278)) (cons (cons .name.2276 (map cadr .formal.2277)) (core#",
"quote ()))))) (core#quote ()))) (car (cdr .form.2274)) (car (cdr (cdr .form.2274",
"))) (cdr (cdr (cdr .form.2274)))) ((core#lambda (.formal.2279 .body.2280) (cons ",
"(cons .the-lambda.2238 (cons (map car .formal.2279) .body.2280)) (map cadr .form",
"al.2279))) (car (cdr .form.2274)) (cdr (cdr .form.2274)))))) (core#begin (.defin",
"e-transformer.2228 (core#quote and) (core#lambda (.form.2281 .env.2282) (core#if",
" (null? (cdr .form.2281)) #t (core#if (null? (cddr .form.2281)) (cadr .form.2281",
") (cons .the-if.2242 (cons (cadr .form.2281) (cons (cons (.the.2229 (core#quote ",
"and)) (cddr .form.2281)) (cons (core#quote #f) (core#quote ()))))))))) (core#beg",
"in (.define-transformer.2228 (core#quote or) (core#lambda (.form.2283 .env.2284)",
" (core#if (null? (cdr .form.2283)) #f ((core#lambda (.tmp.2285) (cons (.the.2229",
" (core#quote let)) (cons (cons (cons .tmp.2285 (cons (cadr .form.2283) (core#quo",
"te ()))) (core#quote ())) (cons (cons .the-if.2242 (cons .tmp.2285 (cons .tmp.22",
"85 (cons (cons (.the.2229 (core#quote or)) (cddr .form.2283)) (core#quote ()))))",
") (core#quote ()))))) (make-identifier (core#quote it) .env.2284))))) (core#begi",
"n (.define-transformer.2228 (core#quote cond) (core#lambda (.form.2286 .env.2287",
") ((core#lambda (.clauses.2288) (core#if (null? .clauses.2288) #undefined ((core",
"#lambda (.clause.2289) (core#if (core#if (identifier? (car .clause.2289)) (ident",
"ifier=? (.the.2229 (core#quote else)) (make-identifier (car .clause.2289) .env.2",
"287)) #f) (cons .the-begin.2239 (cdr .clause.2289)) (core#if (null? (cdr .clause",
".2289)) (cons (.the.2229 (core#quote or)) (cons (car .clause.2289) (cons (cons (",
".the.2229 (core#quote cond)) (cdr .clauses.2288)) (core#quote ())))) (core#if (c",
"ore#if (identifier? (cadr .clause.2289)) (identifier=? (.the.2229 (core#quote =>",
")) (make-identifier (cadr .clause.2289) .env.2287)) #f) ((core#lambda (.tmp.2290",
") (cons (.the.2229 (core#quote let)) (cons (cons (cons .tmp.2290 (cons (car .cla",
"use.2289) (core#quote ()))) (core#quote ())) (cons (cons .the-if.2242 (cons .tmp",
".2290 (cons (cons (cadr (cdr .clause.2289)) (cons .tmp.2290 (core#quote ()))) (c",
"ons (cons (.the.2229 (core#quote cond)) (cddr .form.2286)) (core#quote ()))))) (",
"core#quote ()))))) (make-identifier (core#quote tmp) .env.2287)) (cons .the-if.2",
"242 (cons (car .clause.2289) (cons (cons .the-begin.2239 (cdr .clause.2289)) (co",
"ns (cons (.the.2229 (core#quote cond)) (cdr .clauses.2288)) (core#quote ()))))))",
"))) (car .clauses.2288)))) (cdr .form.2286)))) (core#begin (.define-transformer.",
"2228 (core#quote quasiquote) (core#lambda (.form.2291 .env.2292) (core#begin (co",
"re#define .quasiquote?.2293 (core#lambda (.form.2297) (core#if (pair? .form.2297",
") (core#if (identifier? (car .form.2297)) (identifier=? (.the.2229 (core#quote q",
"uasiquote)) (make-identifier (car .form.2297) .env.2292)) #f) #f))) (core#begin ",
"(core#define .unquote?.2294 (core#lambda (.form.2298) (core#if (pair? .form.2298",
") (core#if (identifier? (car .form.2298)) (identifier=? (.the.2229 (core#quote u",
"nquote)) (make-identifier (car .form.2298) .env.2292)) #f) #f))) (core#begin (co",
"re#define .unquote-splicing?.2295 (core#lambda (.form.2299) (core#if (pair? .for",
"m.2299) (core#if (pair? (car .form.2299)) (core#if (identifier? (caar .form.2299",
")) (identifier=? (.the.2229 (core#quote unquote-splicing)) (make-identifier (caa",
"r .form.2299) .env.2292)) #f) #f) #f))) (core#begin (core#define .qq.2296 (core#",
"lambda (.depth.2300 .expr.2301) (core#if (.unquote?.2294 .expr.2301) (core#if (=",
" .depth.2300 1) (cadr .expr.2301) (list (.the.2229 (core#quote list)) (list (.th",
"e.2229 (core#quote quote)) (.the.2229 (core#quote unquote))) (.qq.2296 (- .depth",
".2300 1) (car (cdr .expr.2301))))) (core#if (.unquote-splicing?.2295 .expr.2301)",
" (core#if (= .depth.2300 1) (list (.the.2229 (core#quote append)) (car (cdr (car",
" .expr.2301))) (.qq.2296 .depth.2300 (cdr .expr.2301))) (list (.the.2229 (core#q",
"uote cons)) (list (.the.2229 (core#quote list)) (list (.the.2229 (core#quote quo",
"te)) (.the.2229 (core#quote unquote-splicing))) (.qq.2296 (- .depth.2300 1) (car",
" (cdr (car .expr.2301))))) (.qq.2296 .depth.2300 (cdr .expr.2301)))) (core#if (.",
"quasiquote?.2293 .expr.2301) (list (.the.2229 (core#quote list)) (list (.the.222",
"9 (core#quote quote)) (.the.2229 (core#quote quasiquote))) (.qq.2296 (+ .depth.2",
"300 1) (car (cdr .expr.2301)))) (core#if (pair? .expr.2301) (list (.the.2229 (co",
"re#quote cons)) (.qq.2296 .depth.2300 (car .expr.2301)) (.qq.2296 .depth.2300 (c",
"dr .expr.2301))) (core#if (vector? .expr.2301) (list (.the.2229 (core#quote list",
"->vector)) (.qq.2296 .depth.2300 (vector->list .expr.2301))) (list (.the.2229 (c",
"ore#quote quote)) .expr.2301)))))))) ((core#lambda (.x.2302) (.qq.2296 1 .x.2302",
")) (cadr .form.2291)))))))) (core#begin (.define-transformer.2228 (core#quote le",
"t*) (core#lambda (.form.2303 .env.2304) ((core#lambda (.bindings.2305 .body.2306",
") (core#if (null? .bindings.2305) (cons (.the.2229 (core#quote let)) (cons (core",
"#quote ()) .body.2306)) (cons (.the.2229 (core#quote let)) (cons (cons (cons (ca",
"r (car .bindings.2305)) (cdr (car .bindings.2305))) (core#quote ())) (cons (cons",
" (.the.2229 (core#quote let*)) (cons (cdr .bindings.2305) .body.2306)) (core#quo",
"te ())))))) (car (cdr .form.2303)) (cdr (cdr .form.2303))))) (core#begin (.defin",
"e-transformer.2228 (core#quote letrec) (core#lambda (.form.2307 .env.2308) (cons",
" (.the.2229 (core#quote letrec*)) (cdr .form.2307)))) (core#begin (.define-trans",
"former.2228 (core#quote letrec*) (core#lambda (.form.2309 .env.2310) ((core#lamb",
"da (.bindings.2311 .body.2312) ((core#lambda (.variables.2313 .initials.2314) (c",
"ons (.the.2229 (core#quote let)) (cons .variables.2313 (append .initials.2314 (a",
"ppend .body.2312 (core#quote ())))))) (map (core#lambda (.v.2315) (cons .v.2315 ",
"(cons (core#quote #undefined) (core#quote ())))) (map car .bindings.2311)) (map ",
"(core#lambda (.v.2316) (cons (.the.2229 (core#quote set!)) (append .v.2316 (core",
"#quote ())))) .bindings.2311))) (car (cdr .form.2309)) (cdr (cdr .form.2309)))))",
" (core#begin (.define-transformer.2228 (core#quote let-values) (core#lambda (.fo",
"rm.2317 .env.2318) (cons (.the.2229 (core#quote let*-values)) (append (cdr .form",
".2317) (core#quote ()))))) (core#begin (.define-transformer.2228 (core#quote let",
"*-values) (core#lambda (.form.2319 .env.2320) ((core#lambda (.formals.2321 .body",
".2322) (core#if (null? .formals.2321) (cons (.the.2229 (core#quote let)) (cons (",
"core#quote ()) (append .body.2322 (core#quote ())))) ((core#lambda (.formal.2323",
") (cons (.the.2229 (core#quote call-with-values)) (cons (cons .the-lambda.2238 (",
"cons (core#quote ()) (cdr .formal.2323))) (cons (cons (.the.2229 (core#quote lam",
"bda)) (cons (car .formal.2323) (cons (cons (.the.2229 (core#quote let*-values)) ",
"(cons (cdr .formals.2321) .body.2322)) (core#quote ())))) (core#quote ()))))) (c",
"ar .formals.2321)))) (cadr .form.2319) (cddr .form.2319)))) (core#begin (.define",
"-transformer.2228 (core#quote define-values) (core#lambda (.form.2324 .env.2325)",
" ((core#lambda (.formal.2326 .body.2327) ((core#lambda (.tmps.2328) (cons .the-b",
"egin.2239 (append ((core#lambda () (core#begin (core#define .loop.2329 (core#lam",
"bda (.formal.2330) (core#if (identifier? .formal.2330) (cons (cons .the-define.2",
"237 (cons .formal.2330 (cons (core#quote #undefined) (core#quote ())))) (core#qu",
"ote ())) (core#if (pair? .formal.2330) (cons (cons .the-define.2237 (cons (car .",
"formal.2330) (cons (core#quote #undefined) (core#quote ())))) (.loop.2329 (cdr .",
"formal.2330))) (core#quote ()))))) (.loop.2329 .formal.2326)))) (cons (cons (.th",
"e.2229 (core#quote call-with-values)) (cons (cons .the-lambda.2238 (cons (core#q",
"uote ()) .body.2327)) (cons (cons .the-lambda.2238 (cons .tmps.2328 ((core#lambd",
"a () (core#begin (core#define .loop.2331 (core#lambda (.formal.2332 .tmps.2333) ",
"(core#if (identifier? .formal.2332) (cons (cons .the-set!.2241 (cons .formal.233",
"2 (cons .tmps.2333 (core#quote ())))) (core#quote ())) (core#if (pair? .formal.2",
"332) (cons (cons .the-set!.2241 (cons (car .formal.2332) (cons (car .tmps.2333) ",
"(core#quote ())))) (.loop.2331 (cdr .formal.2332) (cdr .tmps.2333))) (core#quote",
" ()))))) (.loop.2331 .formal.2326 .tmps.2328)))))) (core#quote ())))) (core#quot",
"e ()))))) ((core#lambda () (core#begin (core#define .loop.2334 (core#lambda (.fo",
"rmal.2335) (core#if (identifier? .formal.2335) (make-identifier .formal.2335 .en",
"v.2325) (core#if (pair? .formal.2335) (cons (make-identifier (car .formal.2335) ",
".env.2325) (.loop.2334 (cdr .formal.2335))) (core#quote ()))))) (.loop.2334 .for",
"mal.2326)))))) (cadr .form.2324) (cddr .form.2324)))) (core#begin (.define-trans",
"former.2228 (core#quote do) (core#lambda (.form.2336 .env.2337) ((core#lambda (.",
"bindings.2338 .test.2339 .cleanup.2340 .body.2341) ((core#lambda (.loop.2342) (c",
"ons (.the.2229 (core#quote let)) (cons .loop.2342 (cons (map (core#lambda (.x.23",
"43) (cons (car .x.2343) (cons (cadr .x.2343) (core#quote ())))) .bindings.2338) ",
"(cons (cons .the-if.2242 (cons .test.2339 (cons (cons .the-begin.2239 .cleanup.2",
"340) (cons (cons .the-begin.2239 (append .body.2341 (cons (cons .loop.2342 (map ",
"(core#lambda (.x.2344) (core#if (null? (cdr (cdr .x.2344))) (car .x.2344) (car (",
"cdr (cdr .x.2344))))) .bindings.2338)) (core#quote ())))) (core#quote ()))))) (c",
"ore#quote ())))))) (make-identifier (core#quote loop) .env.2337))) (car (cdr .fo",
"rm.2336)) (car (car (cdr (cdr .form.2336)))) (cdr (car (cdr (cdr .form.2336)))) ",
"(cdr (cdr (cdr .form.2336)))))) (core#begin (.define-transformer.2228 (core#quot",
"e when) (core#lambda (.form.2345 .env.2346) ((core#lambda (.test.2347 .body.2348",
") (cons .the-if.2242 (cons .test.2347 (cons (cons .the-begin.2239 (append .body.",
"2348 (core#quote ()))) (cons (core#quote #undefined) (core#quote ())))))) (car (",
"cdr .form.2345)) (cdr (cdr .form.2345))))) (core#begin (.define-transformer.2228",
" (core#quote unless) (core#lambda (.form.2349 .env.2350) ((core#lambda (.test.23",
"51 .body.2352) (cons .the-if.2242 (cons .test.2351 (cons (core#quote #undefined)",
" (cons (cons .the-begin.2239 (append .body.2352 (core#quote ()))) (core#quote ()",
")))))) (car (cdr .form.2349)) (cdr (cdr .form.2349))))) (core#begin (.define-tra",
"nsformer.2228 (core#quote case) (core#lambda (.form.2353 .env.2354) ((core#lambd",
"a (.key.2355 .clauses.2356) ((core#lambda (.the-key.2357) (cons (.the.2229 (core",
"#quote let)) (cons (cons (cons .the-key.2357 (cons .key.2355 (core#quote ()))) (",
"core#quote ())) (cons ((core#lambda () (core#begin (core#define .loop.2358 (core",
"#lambda (.clauses.2359) (core#if (null? .clauses.2359) #undefined ((core#lambda ",
"(.clause.2360) (cons .the-if.2242 (cons (core#if (core#if (identifier? (car .cla",
"use.2360)) (identifier=? (.the.2229 (core#quote else)) (make-identifier (car .cl",
"ause.2360) .env.2354)) #f) #t (cons (.the.2229 (core#quote or)) (append (map (co",
"re#lambda (.x.2361) (cons (.the.2229 (core#quote eqv?)) (cons .the-key.2357 (con",
"s (cons .the-quote.2240 (cons .x.2361 (core#quote ()))) (core#quote ()))))) (car",
" .clause.2360)) (core#quote ())))) (cons (core#if (core#if (identifier? (cadr .c",
"lause.2360)) (identifier=? (.the.2229 (core#quote =>)) (make-identifier (cadr .c",
"lause.2360) .env.2354)) #f) (cons (car (cdr (cdr .clause.2360))) (cons .the-key.",
"2357 (core#quote ()))) (cons .the-begin.2239 (append (cdr .clause.2360) (core#qu",
"ote ())))) (cons (.loop.2358 (cdr .clauses.2359)) (core#quote ())))))) (car .cla",
"uses.2359))))) (.loop.2358 .clauses.2356)))) (core#quote ()))))) (make-identifie",
"r (core#quote key) .env.2354))) (car (cdr .form.2353)) (cdr (cdr .form.2353)))))",
" (.define-transformer.2228 (core#quote parameterize) (core#lambda (.form.2362 .e",
"nv.2363) ((core#lambda (.formal.2364 .body.2365) (cons (.the.2229 (core#quote wi",
"th-dynamic-environment)) (cons (cons (.the.2229 (core#quote list)) (append (map ",
"(core#lambda (.x.2366) (cons (.the.2229 (core#quote cons)) (cons (car .x.2366) (",
"cons (cadr .x.2366) (core#quote ()))))) .formal.2364) (core#quote ()))) (cons (c",
"ons .the-lambda.2238 (cons (core#quote ()) (append .body.2365 (core#quote ()))))",
" (core#quote ()))))) (car (cdr .form.2362)) (cdr (cdr .form.2362))))))))))))))))",
")))))))))))))))))) (.the.2229 (core#quote core#define)) (.the.2229 (core#quote c",
"ore#lambda)) (.the.2229 (core#quote core#begin)) (.the.2229 (core#quote core#quo",
"te)) (.the.2229 (core#quote core#set!)) (.the.2229 (core#quote core#if)) (.the.2",
"229 (core#quote core#define-macro)) (.the.2229 (core#quote define)) (.the.2229 (",
"core#quote lambda)) (.the.2229 (core#quote begin)) (.the.2229 (core#quote quote)",
") (.the.2229 (core#quote set!)) (.the.2229 (core#quote if)) (.the.2229 (core#quo",
"te define-macro)))) (core#lambda (.name.2367 .transformer.2368) (dictionary-set!",
" (macro-objects) .name.2367 .transformer.2368)) (core#lambda (.var.2369) (make-i",
"dentifier .var.2369 default-environment)))",
};

#if PIC_USE_LIBRARY
static const char boot_library_rom[][80] = {
"(core#begin (core#define current-library #undefined) (core#begin (core#define fi",
"nd-library #undefined) (core#begin (core#define make-library #undefined) (core#b",
"egin (core#define library-environment #undefined) (core#begin (core#define libra",
"ry-exports #undefined) (core#begin (core#define library-import #undefined) (core",
"#begin (core#define library-export #undefined) (call-with-values (core#lambda ()",
" ((core#lambda () (core#begin (core#define .mangle.2370 (core#lambda (.name.2379",
") (core#begin (core#if (null? .name.2379) (error \"library name should be a list ",
"of at least one symbols\" .name.2379) #undefined) (core#begin (core#define .->str",
"ing.2380 (core#lambda (.n.2382) (core#if (symbol? .n.2382) ((core#lambda (.str.2",
"383) (core#begin (string-for-each (core#lambda (.c.2384) (core#if ((core#lambda ",
"(.it.2385) (core#if .it.2385 .it.2385 ((core#lambda (.it.2386) (core#if .it.2386",
" .it.2386 #f)) (char=? .c.2384 #\\:)))) (char=? .c.2384 #\\.)) (error \"elements of",
" library name may not contain '.' or ':'\" .n.2382) #undefined)) .str.2383) .str.",
"2383)) (symbol->string .n.2382)) (core#if (core#if (number? .n.2382) (core#if (e",
"xact? .n.2382) (<= 0 .n.2382) #f) #f) (number->string .n.2382) (error \"symbol or",
" non-negative integer is required\" .n.2382))))) (core#begin (core#define .join.2",
"381 (core#lambda (.strs.2387 .delim.2388) ((core#lambda () (core#begin (core#def",
"ine .loop.2389 (core#lambda (.res.2390 .strs.2391) (core#if (null? .strs.2391) .",
"res.2390 (.loop.2389 (string-append .res.2390 .delim.2388 (car .strs.2391)) (cdr",
" .strs.2391))))) (.loop.2389 (car .strs.2387) (cdr .strs.2387))))))) (core#if (s",
"ymbol? .name.2379) .name.2379 (string->symbol (.join.2381 (map .->string.2380 .n",
"ame.2379) \".\")))))))) (core#begin (core#define .current-library.2371 (make-param",
"eter (core#quote (picrin user)) .mangle.2370)) (core#begin (core#define .*librar",
"ies*.2372 (make-dictionary)) (core#begin (core#define .find-library.2373 (core#l",
"ambda (.name.2392) (dictionary-has? .*libraries*.2372 (.mangle.2370 .name.2392))",
")) (core#begin (core#define .make-library.2374 (core#lambda (.name.2393) ((core#",
"lambda (.name.2394) ((core#lambda (.env.2395 .exports.2396) (core#begin (set-ide",
"ntifier! (core#quote define-library) (core#quote define-library) .env.2395) (cor",
"e#begin (set-identifier! (core#quote import) (core#quote import) .env.2395) (cor",
"e#begin (set-identifier! (core#quote export) (core#quote export) .env.2395) (cor",
"e#begin (set-identifier! (core#quote cond-expand) (core#quote cond-expand) .env.",
"2395) (dictionary-set! .*libraries*.2372 .name.2394 (cons .env.2395 .exports.239",
"6))))))) (make-environment (string->symbol (string-append (symbol->string .name.",
"2394) \":\"))) (make-dictionary))) (.mangle.2370 .name.2393)))) (core#begin (core#",
"define .library-environment.2375 (core#lambda (.name.2397) (car (dictionary-ref ",
".*libraries*.2372 (.mangle.2370 .name.2397))))) (core#begin (core#define .librar",
"y-exports.2376 (core#lambda (.name.2398) (cdr (dictionary-ref .*libraries*.2372 ",
"(.mangle.2370 .name.2398))))) (core#begin (core#define .library-import.2377 (cor",
"e#lambda (.name.2399 .sym.2400 .alias.2401) ((core#lambda (.uid.2402) ((core#lam",
"bda (.env.2403) (set-identifier! .alias.2401 .uid.2402 .env.2403)) (.library-env",
"ironment.2375 (.current-library.2371)))) (dictionary-ref (.library-exports.2376 ",
".name.2399) .sym.2400)))) (core#begin (core#define .library-export.2378 (core#la",
"mbda (.sym.2404 .alias.2405) ((core#lambda (.env.2406 .exports.2407) (dictionary",
"-set! .exports.2407 .alias.2405 (find-identifier .sym.2404 .env.2406))) (.librar",
"y-environment.2375 (.current-library.2371)) (.library-exports.2376 (.current-lib",
"rary.2371))))) (core#begin ((core#lambda (.define-transformer.2408) (core#begin ",
"(.define-transformer.2408 (core#quote define-library) (core#lambda (.form.2409 .",
"_.2410) ((core#lambda (.name.2411 .body.2412) (core#begin ((core#lambda (.it.241",
"3) (core#if .it.2413 .it.2413 ((core#lambda (.it.2414) (core#if .it.2414 .it.241",
"4 #f)) (.make-library.2374 .name.2411)))) (.find-library.2373 .name.2411)) (with",
"-dynamic-environment (list (cons .current-library.2371 .name.2411)) (core#lambda",
" () (for-each (core#lambda (.expr.2415) (eval .expr.2415 .name.2411)) .body.2412",
"))))) (cadr .form.2409) (cddr .form.2409)))) (core#begin (.define-transformer.24",
"08 (core#quote cond-expand) (core#lambda (.form.2416 ._.2417) ((core#lambda (.te",
"st.2418) (core#begin (core#set! .test.2418 (core#lambda (.form.2419) ((core#lamb",
"da (.it.2420) (core#if .it.2420 .it.2420 ((core#lambda (.it.2421) (core#if .it.2",
"421 .it.2421 ((core#lambda (.it.2422) (core#if .it.2422 .it.2422 #f)) (core#if (",
"pair? .form.2419) ((core#lambda (.key.2423) (core#if ((core#lambda (.it.2424) (c",
"ore#if .it.2424 .it.2424 #f)) (eqv? .key.2423 (core#quote library))) (.find-libr",
"ary.2373 (cadr .form.2419)) (core#if ((core#lambda (.it.2425) (core#if .it.2425 ",
".it.2425 #f)) (eqv? .key.2423 (core#quote not))) (not (.test.2418 (cadr .form.24",
"19))) (core#if ((core#lambda (.it.2426) (core#if .it.2426 .it.2426 #f)) (eqv? .k",
"ey.2423 (core#quote and))) ((core#lambda () (core#begin (core#define .loop.2427 ",
"(core#lambda (.form.2428) ((core#lambda (.it.2429) (core#if .it.2429 .it.2429 ((",
"core#lambda (.it.2430) (core#if .it.2430 .it.2430 #f)) (core#if (.test.2418 (car",
" .form.2428)) (.loop.2427 (cdr .form.2428)) #f)))) (null? .form.2428)))) (.loop.",
"2427 (cdr .form.2419))))) (core#if ((core#lambda (.it.2431) (core#if .it.2431 .i",
"t.2431 #f)) (eqv? .key.2423 (core#quote or))) ((core#lambda () (core#begin (core",
"#define .loop.2432 (core#lambda (.form.2433) (core#if (pair? .form.2433) ((core#",
"lambda (.it.2434) (core#if .it.2434 .it.2434 ((core#lambda (.it.2435) (core#if .",
"it.2435 .it.2435 #f)) (.loop.2432 (cdr .form.2433))))) (.test.2418 (car .form.24",
"33))) #f))) (.loop.2432 (cdr .form.2419))))) (core#if #t #f #undefined)))))) (ca",
"r .form.2419)) #f)))) (core#if (symbol? .form.2419) (memq .form.2419 (features))",
" #f)))) (eq? .form.2419 (core#quote else))))) ((core#lambda () (core#begin (core",
"#define .loop.2436 (core#lambda (.clauses.2437) (core#if (null? .clauses.2437) #",
"undefined (core#if (.test.2418 (caar .clauses.2437)) (cons (make-identifier (cor",
"e#quote begin) default-environment) (append (cdar .clauses.2437) (core#quote ())",
")) (.loop.2436 (cdr .clauses.2437)))))) (.loop.2436 (cdr .form.2416))))))) #unde",
"fined))) (core#begin (.define-transformer.2408 (core#quote import) (core#lambda ",
"(.form.2438 ._.2439) ((core#lambda (.caddr.2440 .prefix.2441 .getlib.2442) ((cor",
"e#lambda (.extract.2443 .collect.2444) (core#begin (core#set! .extract.2443 (cor",
"e#lambda (.spec.2445) ((core#lambda (.key.2446) (core#if ((core#lambda (.it.2447",
") (core#if .it.2447 .it.2447 ((core#lambda (.it.2448) (core#if .it.2448 .it.2448",
" ((core#lambda (.it.2449) (core#if .it.2449 .it.2449 ((core#lambda (.it.2450) (c",
"ore#if .it.2450 .it.2450 #f)) (eqv? .key.2446 (core#quote except))))) (eqv? .key",
".2446 (core#quote prefix))))) (eqv? .key.2446 (core#quote rename))))) (eqv? .key",
".2446 (core#quote only))) (.extract.2443 (cadr .spec.2445)) (core#if #t (.getlib",
".2442 .spec.2445) #undefined))) (car .spec.2445)))) (core#begin (core#set! .coll",
"ect.2444 (core#lambda (.spec.2451) ((core#lambda (.key.2452) (core#if ((core#lam",
"bda (.it.2453) (core#if .it.2453 .it.2453 #f)) (eqv? .key.2452 (core#quote only)",
")) ((core#lambda (.alist.2454) (map (core#lambda (.var.2455) (assq .var.2455 .al",
"ist.2454)) (cddr .spec.2451))) (.collect.2444 (cadr .spec.2451))) (core#if ((cor",
"e#lambda (.it.2456) (core#if .it.2456 .it.2456 #f)) (eqv? .key.2452 (core#quote ",
"rename))) ((core#lambda (.alist.2457 .renames.2458) (map (core#lambda (.s.2459) ",
"((core#lambda (.it.2460) (core#if .it.2460 .it.2460 ((core#lambda (.it.2461) (co",
"re#if .it.2461 .it.2461 #f)) .s.2459))) (assq (car .s.2459) .renames.2458))) .al",
"ist.2457)) (.collect.2444 (cadr .spec.2451)) (map (core#lambda (.x.2462) (cons (",
"car .x.2462) (cadr .x.2462))) (cddr .spec.2451))) (core#if ((core#lambda (.it.24",
"63) (core#if .it.2463 .it.2463 #f)) (eqv? .key.2452 (core#quote prefix))) ((core",
"#lambda (.alist.2464) (map (core#lambda (.s.2465) (cons (.prefix.2441 (.caddr.24",
"40 .spec.2451) (car .s.2465)) (cdr .s.2465))) .alist.2464)) (.collect.2444 (cadr",
" .spec.2451))) (core#if ((core#lambda (.it.2466) (core#if .it.2466 .it.2466 #f))",
" (eqv? .key.2452 (core#quote except))) ((core#lambda (.alist.2467) ((core#lambda",
" () (core#begin (core#define .loop.2468 (core#lambda (.alist.2469) (core#if (nul",
"l? .alist.2469) (core#quote ()) (core#if (memq (caar .alist.2469) (cddr .spec.24",
"51)) (.loop.2468 (cdr .alist.2469)) (cons (car .alist.2469) (.loop.2468 (cdr .al",
"ist.2469))))))) (.loop.2468 .alist.2467))))) (.collect.2444 (cadr .spec.2451))) ",
"(core#if #t (dictionary-map (core#lambda (.x.2470) (cons .x.2470 .x.2470)) (.lib",
"rary-exports.2376 (.getlib.2442 .spec.2451))) #undefined)))))) (car .spec.2451))",
")) ((core#lambda (.import.2471) (core#begin (core#set! .import.2471 (core#lambda",
" (.spec.2472) ((core#lambda (.lib.2473 .alist.2474) (for-each (core#lambda (.slo",
"t.2475) (.library-import.2377 .lib.2473 (cdr .slot.2475) (car .slot.2475))) .ali",
"st.2474)) (.extract.2443 .spec.2472) (.collect.2444 .spec.2472)))) (for-each .im",
"port.2471 (cdr .form.2438)))) #undefined)))) #undefined #undefined)) (core#lambd",
"a (.x.2476) (car (cdr (cdr .x.2476)))) (core#lambda (.prefix.2477 .symbol.2478) ",
"(string->symbol (string-append (symbol->string .prefix.2477) (symbol->string .sy",
"mbol.2478)))) (core#lambda (.name.2479) (core#if (.find-library.2373 .name.2479)",
" .name.2479 (error \"library not found\" .name.2479)))))) (.define-transformer.240",
"8 (core#quote export) (core#lambda (.form.2480 ._.2481) ((core#lambda (.collect.",
"2482 .export.2483) (core#begin (core#set! .collect.2482 (core#lambda (.spec.2484",
") (core#if (symbol? .spec.2484) (cons .spec.2484 .spec.2484) (core#if (core#if (",
"list? .spec.2484) (core#if (= (length .spec.2484) 3) (eq? (car .spec.2484) (core",
"#quote rename)) #f) #f) (cons (list-ref .spec.2484 1) (list-ref .spec.2484 2)) (",
"error \"malformed export\"))))) (core#begin (core#set! .export.2483 (core#lambda (",
".spec.2485) ((core#lambda (.slot.2486) (.library-export.2378 (car .slot.2486) (c",
"dr .slot.2486))) (.collect.2482 .spec.2485)))) (for-each .export.2483 (cdr .form",
".2480))))) #undefined #undefined))))))) (core#lambda (.name.2487 .macro.2488) (d",
"ictionary-set! (macro-objects) .name.2487 .macro.2488))) (core#begin ((core#lamb",
"da () (core#begin (.make-library.2374 (core#quote (picrin base))) (core#begin (s",
"et-car! (dictionary-ref .*libraries*.2372 (.mangle.2370 (core#quote (picrin base",
")))) default-environment) (core#begin ((core#lambda (.exports.2489) ((core#lambd",
"a (.export-keyword.2490) ((core#lambda () (core#begin (for-each .export-keyword.",
"2490 (core#quote (define lambda quote set! if begin define-macro let let* letrec",
" letrec* let-values let*-values define-values quasiquote unquote unquote-splicin",
"g and or cond case else => do when unless parameterize))) (core#begin (.export-k",
"eyword.2490 (core#quote boolean?)) (dictionary-for-each .export-keyword.2490 (gl",
"obal-objects))))))) (core#lambda (.keyword.2491) (dictionary-set! .exports.2489 ",
".keyword.2491 .keyword.2491)))) (.library-exports.2376 (core#quote (picrin base)",
"))) (core#begin (core#set! eval ((core#lambda (.e.2492) (core#lambda (.expr.2493",
" . .lib.2494) ((core#lambda (.lib.2495) (.e.2492 .expr.2493 (.library-environmen",
"t.2375 .lib.2495))) (core#if (null? .lib.2494) (.current-library.2371) (car .lib",
".2494))))) eval)) (.make-library.2374 (core#quote (picrin user))))))))) (values ",
".current-library.2371 .find-library.2373 .make-library.2374 .library-environment",
".2375 .library-exports.2376 .library-import.2377 .library-export.2378)))))))))))",
")))) (core#lambda (.current-library.2496 .find-library.2497 .make-library.2498 .",
"library-environment.2499 .library-exports.2500 .library-import.2501 .library-exp",
"ort.2502) (core#begin (core#set! current-library .current-library.2496) (core#be",
"gin (core#set! find-library .find-library.2497) (core#begin (core#set! make-libr",
"ary .make-library.2498) (core#begin (core#set! library-environment .library-envi",
"ronment.2499) (core#begin (core#set! library-exports .library-exports.2500) (cor",
"e#begin (core#set! library-import .library-import.2501) (core#set! library-expor",
"t .library-export.2502))))))))))))))))",
};
#endif

void
pic_boot(pic_state *pic)
{
  pic_load_native(pic, &boot_rom[0][0]);
#if PIC_USE_LIBRARY
  pic_load_native(pic, &boot_library_rom[0][0]);
#endif
}
