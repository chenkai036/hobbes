/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "hexpr.y" /* yacc.c:337  */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1

#define YYLLOC_DEFAULT(L, R, N) \
  if (N) { \
    (L).first_line   = YYRHSLOC(R, 1).first_line; \
    (L).first_column = YYRHSLOC(R, 1).first_column; \
    (L).last_line    = YYRHSLOC(R, N).last_line; \
    (L).last_column  = YYRHSLOC(R, N).last_column; \
  } else { \
    (L).first_line = (L).last_line = YYRHSLOC(R, 0).last_line; \
    (L).first_column = (L).last_column = YYRHSLOC(R, 0).last_column; \
  }
#line 25 "hexpr.y" /* yacc.c:337  */

#include <hobbes/lang/module.H>
#include <hobbes/lang/expr.H>
#include <hobbes/lang/pat/pattern.H>
#include <hobbes/lang/type.H>
#include <hobbes/lang/typepreds.H>
#include <hobbes/db/bindings.H>
#include <hobbes/util/autorelease.H>
#include <hobbes/util/str.H>
#include <hobbes/util/array.H>
#include <hobbes/parse/grammar.H>
#include <hobbes/parse/lalr.H>
#include <hobbes/read/pgen/hexpr.parse.H>
#include <string>
#include <stdexcept>
#include <vector>
#include <stdio.h>

using namespace hobbes;

typedef std::pair<PatternPtr, ExprPtr> LetBinding;
typedef std::vector<LetBinding>        LetBindings;

cc*         yyParseCC;
Module*     yyParsedModule = 0;
std::string yyParsedVar;
Expr*       yyParsedExpr   = 0;
std::string yyMatchDiagram;
std::string yyModulePath;
YYLTYPE     yyErrPos;

extern std::string yyVexpLexError;

extern void wantIndent(bool f);

extern int yylex();
void yyerror(const char* s) {
  yyVexpLexError = std::string(s);
  yyErrPos       = yylloc;
}

LexicalAnnotation m(const YYLTYPE& p) {
  return LexicallyAnnotated::make(Pos(p.first_line, p.first_column), Pos(p.last_line, p.last_column));
}

LexicalAnnotation m(const YYLTYPE& p0, const YYLTYPE& p1) {
  return LexicallyAnnotated::make(Pos(p0.first_line, p0.first_column), Pos(p1.last_line, p1.last_column));
}

#define TAPP0(fn,la)          new App(fn, list<ExprPtr>(), la)
#define TAPP1(fn,x0,la)       new App(fn, list(ExprPtr(x0)), la)
#define TAPP2(fn,x0,x1,la)    new App(fn, list(ExprPtr(x0),ExprPtr(x1)), la)
#define TAPP3(fn,x0,x1,x2,la) new App(fn, list(ExprPtr(x0),ExprPtr(x1),ExprPtr(x2)), la)

Expr* pickNestedExp(Exprs* exprs, const LexicalAnnotation& la) {
  if (exprs->size() == 0) {
    return new Unit(la);
  } else if (exprs->size() == 1) {
    auto expr = (*exprs)[0]->clone();
    auto annotation = expr->la();
    annotation.span = la.span;
    expr->la(annotation);
    return expr;
  } else {
    MkRecord::FieldDefs fds;
    for (size_t i = 0; i < exprs->size(); ++i) {
      fds.push_back(MkRecord::FieldDef(".f" + str::from(i), (*exprs)[i]));
    }
    return new MkRecord(fds, la);
  }
}

Pattern* pickNestedPat(Patterns* pats, const LexicalAnnotation& la) {
  if (pats->size() == 0) {
    return new MatchLiteral(PrimitivePtr(new Unit(la)), la);
  } else {
    MatchRecord::Fields fds;
    for (size_t i = 0; i < pats->size(); ++i) {
      fds.push_back(MatchRecord::Field(".f" + str::from(i), (*pats)[i]));
    }
    return new MatchRecord(fds, la);
  }
}

PatternRows normPatternRules(PatternRows rs, const LexicalAnnotation& la) {
  if (rs.size() > 0 && !rs.back().result) {
    throw annotated_error(la, "match table can't end with fall-through row");
  }

  for (size_t i = rs.size(); i > 0; --i) {
    if (!rs[i-1].result) {
      rs[i-1].result = rs[i].result;
    }
  }
  return rs;
}

Expr* compileNestedLetMatch(const LetBindings& bs, const ExprPtr& e, const LexicalAnnotation& la) {
  ExprPtr r = e;
  for (LetBindings::const_reverse_iterator b = bs.rbegin(); b != bs.rend(); ++b) {
    r = compileMatch(yyParseCC, list(b->second), list(PatternRow(list(b->first), r)), la);
  }
  return r->clone();
}

Expr* makeRefutablePatternFn(const Patterns& ps, const ExprPtr& e, const LexicalAnnotation& la) {
  str::seq vns;
  Exprs    vnes;
  Patterns els;
  for (size_t i = 0; i < ps.size(); ++i) {
    std::string vname = ".arg" + str::from(i);
    vns.push_back(vname);
    vnes.push_back(isUnitPat(ps[i]) ? assume(var(vname, la), primty("unit"), la) : var(vname, la));
    els.push_back(PatternPtr(new MatchAny("_", la)));
  }
  return
    new Fn(vns,
      compileMatch(yyParseCC, vnes, list(
        PatternRow(ps,  justE(e, la)),
        PatternRow(els, nothingE(la))
      ), la),
      la
    );
}

Expr* makeIrrefutablePatternFn(const Patterns& ps, const ExprPtr& e, const LexicalAnnotation& la) {
  str::seq vns;
  Exprs    vnes;
  for (size_t i = 0; i < ps.size(); ++i) {
    std::string vname = ".arg" + str::from(i);
    vns.push_back(vname);
    vnes.push_back(isUnitPat(ps[i]) ? assume(var(vname, la), primty("unit"), la) : var(vname, la));
  }
  return new Fn(vns, compileMatch(yyParseCC, vnes, list(PatternRow(ps, e)), la), la);
}

Expr* makePatternFn(const Patterns& ps, const ExprPtr& e, const LexicalAnnotation& la) {
  for (const auto p : ps) {
    if (refutable(p)) {
      return makeRefutablePatternFn(ps, e, la);
    }
  }
  return makeIrrefutablePatternFn(ps, e, la);
}

Expr* makeProjSeq(Expr* rec, const str::seq& fields, const LexicalAnnotation& la) {
  for (const auto& f : fields) {
    rec = new Proj(ExprPtr(rec), f, la);
  }
  return rec;
}

MonoTypePtr monoTypeByName(const std::string& tn) {
  if (isPrimName(tn) || yyParseCC->isTypeAliasName(tn)) {
    return yyParseCC->replaceTypeAliases(Prim::make(tn));
  } else if (yyParseCC->isTypeName(tn)) {
    return Prim::make(tn, yyParseCC->namedTypeRepresentation(tn));
  } else {
    return TVar::make(tn);
  }
}

MonoTypePtr accumTApp(const MonoTypes& ts) {
  if (ts.size() == 0) {
    throw std::runtime_error("Internal parser error for type applications");
  } else if (ts.size() == 1) {
    return ts[0];
  } else {
    return MonoTypePtr(TApp::make(ts[0], drop(ts, 1)));
  }
}

MonoTypePtr makeTupleType(const MonoTypes& mts) {
  if (mts.size() == 1) {
    return clone(mts[0]);
  } else {
    Record::Members tms;
    for (unsigned int i = 0; i < mts.size(); ++i) {
      tms.push_back(Record::Member(".f" + str::from(i), mts[i]));
    }
    return Record::make(tms);
  }
}

MonoTypePtr makeSumType(const MonoTypes& mts) {
  Variant::Members ms;
  for (unsigned int i = 0; i < mts.size(); ++i) {
    ms.push_back(Variant::Member(".f" + str::from(i), mts[i], i));
  }
  return Variant::make(ms);
}

MonoTypePtr makeRecType(const Record::Members& tms) {
  return Record::make(tms);
}

MonoTypePtr makeVarType(const Variant::Members& vms) {
  Variant::Members tvms = vms;
  for (unsigned int i = 0; i < tvms.size(); ++i) {
    tvms[i].id = i;
  }
  return Variant::make(tvms);
}

str::seq tupSectionFields(const std::string& x) {
  str::seq r = str::csplit(x.substr(1), ".");
  for (std::string& f : r) {
    f = ".f" + f;
  }
  return r;
}

// override var and pat-var construction
namespace hobbes {
typedef Expr* (*VarCtorFn)(const std::string&, const LexicalAnnotation&);
typedef Pattern* (*PatVarCtorFn)(const std::string&, const LexicalAnnotation&);
extern VarCtorFn varCtorFn;
extern PatVarCtorFn patVarCtorFn;
}


#line 315 "hexpr.parse.C" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "hexpr.parse.H".  */
#ifndef YY_YY_HEXPR_PARSE_H_INCLUDED
# define YY_YY_HEXPR_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TPARSEMODULE = 258,
    TPARSEDEFN = 259,
    TPARSEEXPR = 260,
    TOPTION = 261,
    TMODULE = 262,
    TWHERE = 263,
    TIMPORT = 264,
    TTYPE = 265,
    TDATA = 266,
    TCLASS = 267,
    TINST = 268,
    TINDENT = 269,
    TBOOL = 270,
    TCHAR = 271,
    TBYTE = 272,
    TBYTES = 273,
    TSHORT = 274,
    TINT = 275,
    TLONG = 276,
    TINT128 = 277,
    TFLOAT = 278,
    TDOUBLE = 279,
    TIDENT = 280,
    TSTRING = 281,
    TREGEX = 282,
    TTIMEINTERVAL = 283,
    TTIME = 284,
    TDATETIME = 285,
    TTUPSECTION = 286,
    TCSTARROW = 287,
    TARROW = 288,
    TCOLON = 289,
    TEXISTS = 290,
    TASSIGN = 291,
    TPARROW = 292,
    TEQUALS = 293,
    TASSUMP = 294,
    TAPPEND = 295,
    TPLUS = 296,
    TMINUS = 297,
    TTIMES = 298,
    TDIVIDE = 299,
    TREM = 300,
    TDOT = 301,
    TEQUIV = 302,
    TEQ = 303,
    TCIEQ = 304,
    TNEQ = 305,
    TLT = 306,
    TLTE = 307,
    TGT = 308,
    TGTE = 309,
    TNOT = 310,
    TLET = 311,
    TCASE = 312,
    TDEFAULT = 313,
    TMATCH = 314,
    TMATCHES = 315,
    TPARSE = 316,
    TWITH = 317,
    TOF = 318,
    TAND = 319,
    TOR = 320,
    TIF = 321,
    TTHEN = 322,
    TELSE = 323,
    TIN = 324,
    TPACK = 325,
    TUNPACK = 326,
    TDO = 327,
    TRETURN = 328,
    TLPAREN = 329,
    TRPAREN = 330,
    TLBRACKET = 331,
    TRBRACKET = 332,
    TLBRACE = 333,
    TRBRACE = 334,
    TBAR = 335,
    TCOMMA = 336,
    TSEMICOLON = 337,
    TFN = 338,
    TFNL = 339,
    TCOMPOSE = 340,
    TUPTO = 341,
    TCARET = 342,
    TAT = 343,
    TDOLLAR = 344,
    TQUESTION = 345,
    TSQUOTE = 346,
    TEQUOTE = 347
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 251 "hexpr.y" /* yacc.c:352  */

  hobbes::Module*              module;
  hobbes::ModuleDefs*          mdefs;
  hobbes::ModuleDef*           mdef;
  hobbes::CFunDepDef*          fundep;
  hobbes::CFunDepDefs*         fundeps;
  hobbes::MVarTypeDefs*        mvtydefs;
  hobbes::MVarTypeDef*         mvtydef;
  hobbes::MVarDefs*            mvdefs;
  hobbes::MVarDef*             mvdef;
  hobbes::str::seq*            strings;

  hobbes::Expr*                exp;
  hobbes::Exprs*               exps;
  hobbes::MkRecord::FieldDefs* rfields;
  hobbes::Case::Bindings*      vfields;
  hobbes::Case::Binding*       vbind;

  hobbes::PatternRows*         patternexps;
  hobbes::PatternRow*          patternexp;
  hobbes::Patterns*            patterns;
  hobbes::Pattern*             pattern;
  hobbes::CSelection*          cselection;
  hobbes::CSelections*         cselections;
  hobbes::MatchRecord::Fields* recpatfields;
  hobbes::MatchRecord::Field*  recpatfield;

  typedef std::pair<hobbes::PatternPtr, hobbes::ExprPtr> LetBinding;
  typedef std::vector<LetBinding>                        LetBindings;

  LetBinding*                             letbinding;
  LetBindings*                            letbindings;

  hobbes::QualType*            qualtype;
  hobbes::Constraints*         tconstraints;
  hobbes::Constraint*          tconstraint;
  const hobbes::MonoTypePtr*   mtype;
  hobbes::MonoTypes*           mtypes;
  hobbes::Record::Members*     mreclist;
  hobbes::Variant::Members*    mvarlist;

  std::string*                            string;
  bool                                    boolv;
  char                                    charv;
  short                                   shortv;
  int                                     intv;
  long                                    longv;
  __int128                                int128v;
  float                                   floatv;
  double                                  doublev;

  hobbes::Grammar*             prules;
  hobbes::Grammar::value_type* prule;
  hobbes::GrammarRules*        prdefs;
  hobbes::GrammarRule*         prdef;
  hobbes::BoundGrammarValues*  pbelems;
  hobbes::BoundGrammarValue*   pbelem;
  hobbes::GrammarValue*        pvalue;

#line 511 "hexpr.parse.C" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HEXPR_PARSE_H_INCLUDED  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2910

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  351
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  771

#define YYUNDEFTOK  2
#define YYMAXUTOK   348

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   473,   473,   474,   475,   476,   479,   480,   481,   483,
     484,   485,   487,   488,   489,   490,   491,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   507,
     510,   513,   514,   517,   519,   522,   523,   524,   525,   526,
     527,   528,   529,   531,   532,   534,   536,   537,   539,   542,
     543,   544,   545,   547,   548,   550,   553,   555,   557,   558,
     560,   562,   564,   565,   566,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   584,   585,   587,   588,   591,   592,   593,   594,   596,
     597,   598,   599,   600,   601,   603,   604,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   616,   617,   618,   619,
     620,   622,   623,   624,   625,   627,   630,   631,   634,   637,
     640,   652,   653,   656,   658,   659,   661,   663,   664,   666,
     667,   669,   670,   672,   673,   675,   676,   679,   680,   683,
     684,   685,   686,   687,   688,   689,   690,   693,   694,   695,
     696,   697,   700,   701,   702,   705,   708,   711,   712,   715,
     716,   717,   718,   719,   720,   721,   722,   723,   724,   725,
     726,   727,   728,   731,   734,   735,   736,   737,   738,   739,
     740,   741,   742,   743,   744,   745,   746,   747,   748,   749,
     750,   751,   754,   756,   757,   759,   761,   762,   764,   766,
     767,   769,   770,   772,   773,   774,   776,   777,   779,   780,
     782,   783,   785,   786,   789,   790,   792,   793,   794,   795,
     796,   797,   798,   799,   800,   801,   802,   803,   804,   805,
     806,   807,   808,   809,   810,   811,   812,   813,   814,   815,
     817,   818,   819,   820,   821,   823,   825,   826,   828,   829,
     831,   832,   834,   836,   837,   838,   840,   841,   842,   843,
     844,   845,   846,   847,   848,   849,   850,   851,   852,   853,
     855,   856,   857,   858,   860,   861,   863,   864,   865,   867,
     868,   869,   871,   872,   875,   877,   878,   880,   881,   882,
     883,   884,   885,   886,   887,   888,   889,   891,   892,   893,
     894,   896,   897,   898,   899,   901,   902,   903,   905,   906,
     908,   909,   911,   912,   913,   915,   916,   917,   918,   919,
     920,   921,   922,   923,   924,   925,   926,   927,   928,   929,
     930,   931,   932,   934,   935,   937,   938,   940,   941,   943,
     944,   946,   947,   949,   950,   952,   953,   955,   956,   957,
     958,   960
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"domodule\"", "\"dodefn\"",
  "\"doexpr\"", "\"option\"", "\"module\"", "\"where\"", "\"import\"",
  "\"type\"", "\"data\"", "\"class\"", "\"instance\"", "\"indent\"",
  "\"boolV\"", "\"charV\"", "\"byteV\"", "\"bytesV\"", "\"shortV\"",
  "\"intV\"", "\"longV\"", "\"int128V\"", "\"floatV\"", "\"doubleV\"",
  "\"id\"", "\"stringV\"", "\"regexV\"", "\"timespanV\"", "\"timeV\"",
  "\"dateTimeV\"", "\"tupSection\"", "\"=>\"", "\"->\"", "\":\"",
  "\"exists\"", "\"<-\"", "\":=\"", "\"=\"", "\"::\"", "\"++\"", "\"+\"",
  "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\".\"", "\"==\"", "\"===\"",
  "\"~\"", "\"!=\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"", "\"!\"",
  "\"let\"", "\"case\"", "\"default\"", "\"match\"", "\"matches\"",
  "\"parse\"", "\"with\"", "\"of\"", "\"and\"", "\"or\"", "\"if\"",
  "\"then\"", "\"else\"", "\"in\"", "\"pack\"", "\"unpack\"", "\"do\"",
  "\"return\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\"|\"", "\",\"", "\";\"", "\"\\\\\"", "\"fn\"", "\"o\"", "\"..\"",
  "\"^\"", "\"@\"", "\"$\"", "\"?\"", "\"'\"", "\"`\"", "\"=~\"",
  "$accept", "s", "module", "defs", "def", "importdef", "tydef",
  "vartybind", "vardef", "classdef", "fundeps", "fundep", "cmembers",
  "cmember", "instdef", "imembers", "imember", "names", "nameseq", "name",
  "opname", "idseq", "types", "l0expr", "lhexpr", "l1expr", "l2expr",
  "l3expr", "l4expr", "l5expr", "letbindings", "letbinding", "dobindings",
  "dobinding", "cselconds", "cselection", "cselections", "l6expr",
  "prules", "prule", "prdefs", "prdef", "pbelems", "pbelem", "pvalue",
  "tsseq", "l6exprs", "patternexps", "patternexp", "patterns",
  "refutablep", "irrefutablep", "pattern", "patternseq", "patternseqn",
  "recpatfields", "recpatfield", "recfields", "recfieldname",
  "recfieldpath", "varfields", "varbind", "cargs", "qtype", "cst",
  "tpreds", "tpred", "l1mtargl", "ltmtype", "l0mtype", "l1mtype", "tyind",
  "cppid", "l0mtargl", "l0mtarglt", "mtuplist", "msumlist", "mreclist",
  "mvarlist", "id", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348
};
# endif

#define YYPACT_NINF -580

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-580)))

#define YYTABLE_NINF -351

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     447,  1422,  2195,  2195,    41,   178,   178,   178,    81,    81,
      82,    82,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,   852,
      59,  2195,   334,   -23,   334,   178,    -7,  1648,  2195,   852,
     375,  2195,  -580,   471,  -580,  -580,  -580,  -580,  -580,  -580,
     138,  -580,   252,    38,    31,   223,  2585,  2429,  2195,  1727,
    1511,  1511,  -580,    37,   160,   391,   464,   465,  -580,   233,
    -580,  -580,  -580,  1422,    68,   232,  -580,  1067,   102,  -580,
    -580,   126,  2077,   257,    81,   271,  2155,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,  -580,  1511,   178,     3,  -580,   302,  -580,   318,   192,
    2741,   178,   192,   310,  2273,   291,   328,  2507,   359,   372,
     384,   852,   389,   401,   445,   449,   450,   451,   454,   458,
     874,   460,   462,   469,  -580,  -580,   473,  -580,   174,   289,
     347,   352,   371,   477,   114,   335,  -580,  2233,  2233,  1511,
    2195,  1961,    31,  -580,  -580,   852,  2195,   122,  -580,  -580,
     418,   291,   328,  2507,   359,   372,   384,   389,   401,   445,
     450,   451,   454,   458,   460,   462,   469,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    1511,  1511,   178,   382,    38,  2764,  -580,  -580,  -580,  2830,
    1527,  1527,  1527,  1527,  2429,  2585,  2585,  2585,  2585,  2585,
    2585,  2585,  2585,  2585,  2585,  2585,  2663,  2663,  2663,  2195,
    -580,   471,   178,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    2233,  -580,  2233,  -580,  -580,  -580,   178,   178,   634,   219,
    2311,  2311,   178,  2195,   296,  -580,   149,  2311,   178,    30,
      81,  1067,   178,   634,   178,   178,    39,  -580,    16,   489,
     495,   498,  -580,  -580,   298,   459,   398,  -580,   508,  2195,
      19,  2429,   470,   472,   192,    20,  -580,   516,   334,  1805,
     852,   474,  1883,  -580,   517,   519,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  2195,  1511,  2039,  -580,
    -580,   723,  2195,  2195,  2195,  -580,  -580,  1200,  -580,   522,
    -580,  -580,  -580,   307,  2195,    84,  -580,  -580,  2195,   182,
    2195,   308,   348,   437,   521,   131,  2195,  -580,  2195,   162,
     475,   475,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,   471,
    -580,  -580,  -580,   515,   197,   487,  -580,  1317,  -580,     7,
    2155,  -580,   996,   634,    51,   440,   530,   104,   313,    49,
     523,   478,  -580,  2077,   294,  2311,  2311,   852,  2311,  2311,
    2311,  1999,  2311,   479,    81,   551,   178,   178,  2155,   490,
     538,   539,   560,  -580,  2311,  2311,  2311,  2311,  -580,   500,
    1511,  -580,    21,  1511,  -580,  2195,  -580,  -580,   386,  1511,
     472,  -580,  -580,  -580,  -580,   132,  -580,  -580,  -580,  -580,
    -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  -580,  1805,
    2351,   852,   393,    38,  -580,   508,  -580,  2195,  -580,  -580,
    2195,  -580,  -580,   342,   541,  -580,   502,  -580,   542,  -580,
     501,   503,   634,   172,  2155,  -580,   505,  2117,  -580,  -580,
    2195,   203,   525,  -580,   510,  -580,   513,  -580,    45,  1511,
    1511,  -580,  -580,  -580,  2311,  -580,  -580,  -580,  -580,  2311,
     514,  -580,  2311,  -580,   178,  2155,  2311,  2155,  -580,   178,
    2155,  2311,  -580,  -580,  2311,  2311,  2311,    23,    53,   410,
     479,   479,   479,  -580,   479,   479,    34,    81,   551,  -580,
      24,  -580,   146,  -580,  -580,   189,  2155,  2155,  2155,    81,
     560,  -580,   479,   479,   479,   479,  -580,  -580,  -580,  -580,
    -580,  -580,   568,   373,  -580,   303,  1606,  -580,   524,  -580,
      42,   334,   565,   152,   526,   527,  -580,  1511,  2195,  -580,
    2195,  -580,  -580,  -580,  -580,  -580,   533,  -580,  2195,   208,
    2195,  -580,  -580,  -580,   531,   532,   479,   184,   395,    65,
     579,  -580,    10,   239,   534,   581,   536,    46,   479,    93,
     137,   583,    87,   584,  2311,  2311,  2311,  2311,  2311,   551,
     178,  -580,  -580,   551,   178,   178,  -580,   560,  -580,   317,
    -580,  -580,   585,  -580,   178,   563,   386,   178,  2195,  2195,
    2195,  -580,  -580,  -580,  2195,  -580,  -580,   588,   192,  2351,
    2351,  -580,  -580,  -580,  -580,   543,  -580,  -580,  -580,  2195,
     248,  -580,  -580,  -580,   593,  -580,   600,  -580,   597,  2155,
    2311,   598,   601,  2155,   602,  2311,  2311,  2311,  2311,  2311,
    2311,   479,   479,   479,   479,   479,   551,    27,   551,  -580,
     178,   560,  -580,  2155,  2195,   604,  2195,  -580,   605,  -580,
     606,  -580,  -580,   567,   299,  1527,  -580,  2195,   249,  2311,
     571,  2311,  -580,    71,  2311,  2311,  -580,  2311,   254,   200,
     206,   143,   255,    97,   551,  -580,  -580,  2195,  -580,  2195,
    2195,  -580,  -580,  -580,   162,   572,  -580,  2195,   275,   479,
    -580,   479,   614,   479,   479,   479,   617,  -580,  -580,  2311,
    -580,  2311,   551,  -580,  -580,  -580,  1527,  -580,  2195,   279,
    2311,  2311,   213,   259,   162,  -580,  2195,   285,   479,   479,
    -580,  -580,  -580,  2195,   293,  -580,  2195,   618,  -580,  2195,
    -580
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   351,   169,   156,   206,   171,   172,   273,     0,
       0,     0,     0,     0,     0,     0,     0,   279,   279,   253,
       0,     0,     2,     8,    10,    12,    13,    14,    15,    16,
       0,    29,   115,   170,   155,   138,     0,     0,     0,   279,
       0,     0,     4,    88,    94,    96,   105,   110,   114,   138,
       5,   138,     1,     9,     0,    30,   335,     0,     0,    58,
      60,     0,     0,     0,     0,     0,     0,   264,   259,   263,
     258,   257,   260,   261,   269,   262,   265,   266,   267,   268,
     272,   256,   247,     0,     0,   125,     0,   240,     0,   209,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    67,     0,   280,     0,   280,
       0,     0,     0,     0,     0,     0,    11,     0,     0,     0,
     279,     0,   154,   207,   271,     0,     0,     0,   109,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   216,   217,   218,
     224,   219,   220,   221,   222,   223,   225,   229,   227,   228,
     247,   247,     0,     0,   226,     0,   245,   215,   239,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     9,     0,    75,    76,    77,    78,    79,    80,    65,
      69,    68,    66,    70,    71,    72,    73,    62,    63,    74,
       0,    59,     0,   326,   325,   331,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   285,     0,   315,     0,    39,
      56,    60,     0,     0,     0,     0,    49,    83,   341,     0,
     313,   314,   315,   249,     0,   246,     0,   251,     0,     0,
       0,     0,     0,     0,   208,     0,   194,     0,     0,   247,
     253,     0,     0,   128,     0,   138,   174,   175,   176,   177,
     178,   179,   182,   181,   180,   183,   184,   187,   185,   186,
     191,   188,   189,   190,    61,   173,     0,     0,     0,   142,
     152,     0,     0,     0,     0,   149,   192,     0,    33,     0,
     283,   123,   119,     0,     0,     0,   270,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   214,     0,    87,
      90,    91,    92,    93,    99,    98,    97,   100,   101,   102,
     103,   104,   108,   106,   107,   111,   112,   113,     3,     7,
     336,    31,    32,     0,     0,     0,   324,     0,   311,   341,
       0,   317,     0,     0,     0,     0,   315,     0,     0,   315,
       0,     0,   284,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,   308,     0,     0,     0,     0,     0,   311,
       0,   350,     0,    84,     0,     0,     0,     0,   241,     0,
       0,   243,     0,     0,   116,     0,   124,   126,     0,     0,
     118,   211,   120,   193,   200,     0,   159,   160,   161,   162,
     163,   164,   165,   166,   168,   169,   156,   171,   172,   247,
     247,   253,     0,   170,   138,     0,   130,     0,   121,   127,
       0,   281,   136,     0,     0,   140,     0,   153,     0,   254,
       0,     0,     0,   341,     0,   137,     0,     0,   143,    18,
       0,     0,     0,   235,     0,   230,     0,   237,     0,     0,
       0,   232,    85,    86,     0,   316,   320,   321,   310,     0,
       0,   318,     0,   322,     0,     0,     0,     0,   323,     0,
       0,     0,   332,   286,     0,     0,     0,     0,     0,     0,
     288,   290,   289,   329,   328,   309,    35,     0,    41,    46,
      40,    43,     0,    81,    57,    50,     0,     0,     0,     0,
      51,    53,   343,   312,   342,   344,   242,   248,   244,   250,
     252,   117,     0,     0,   274,     0,     0,   210,   195,   197,
       0,     0,     0,     0,     0,     0,   141,     0,     0,   139,
       0,   148,   147,   282,   146,   145,     0,    19,     0,     0,
       0,   236,   231,   238,     0,     0,   327,     0,     0,     0,
       0,   346,   341,     0,     0,   348,   349,   341,   330,     0,
       0,   315,     0,   315,     0,     0,     0,     0,     0,     0,
       0,    48,    47,     0,     0,     0,    82,     0,   339,     0,
     349,    55,     0,    54,     0,   150,     0,     0,     0,     0,
       0,   200,   205,   204,     0,   199,   202,   203,   158,     0,
       0,   149,   122,   129,   135,   134,   255,   144,    20,     0,
       0,    95,   234,   233,     0,   334,     0,   333,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,   300,   299,   298,   297,    37,    36,    42,    44,
      45,    52,   338,     0,     0,     0,     0,   275,     0,   276,
       0,   212,   196,     0,     0,     0,    21,     0,     0,     0,
       0,     0,   345,     0,     0,     0,   347,     0,   343,     0,
       0,     0,     0,     0,     0,   340,    34,     0,   151,     0,
       0,   198,   201,   203,   132,   133,    22,     0,     0,   296,
     319,   294,     0,   302,   306,   305,     0,   293,   291,     0,
     301,     0,    38,   278,   277,   213,     0,    23,     0,     0,
       0,     0,     0,     0,   131,    24,     0,     0,   295,   304,
     292,   303,    25,     0,     0,    26,     0,     0,    27,     0,
      28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -580,  -580,   589,   423,   -24,  -580,  -580,   130,  -580,  -580,
      48,    47,  -579,  -506,  -580,    56,  -514,  -371,   321,    -3,
     403,    50,   258,    -2,  -188,   -39,   260,   -31,   295,     9,
    -580,   390,  -580,   383,  -580,   110,  -580,   -30,  -580,   394,
    -580,    52,  -580,  -580,   -16,   -33,  -580,  -580,   250,   -45,
    -580,   -90,   -53,  -170,  -580,  -169,  -385,  -580,   -12,   -49,
    -580,    55,   -29,  -117,   463,  -580,   297,  -580,   438,   -75,
     911,  -580,   439,  -580,  -580,  -580,  -580,  -580,  -580,   590
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    42,    43,    44,    45,    46,    47,   621,    48,
     530,   531,   528,   529,    49,   540,   541,   259,   260,    50,
     136,   532,   266,   137,    63,    64,    65,    66,    67,    68,
     104,   105,   292,   293,   725,   462,   463,    52,   285,   286,
     558,   559,   560,   635,   636,    53,   110,   430,   431,   195,
     196,   106,   273,   274,   275,   276,   277,   141,   142,    54,
     553,   554,   138,   328,   329,   254,   255,   402,   377,   330,
     268,   656,    75,   269,   619,   270,   271,   385,   388,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    70,   109,   152,   112,    79,    79,   197,   197,   140,
      51,   267,   349,   350,   351,   352,   199,   100,   159,   146,
     341,   342,   612,   343,   294,   158,   623,   194,   194,   108,
     676,   331,   613,   526,   678,   714,   139,   549,   405,   145,
    -337,    72,   609,  -337,    22,    22,    22,   412,   414,  -337,
     499,   414,    51,   660,   243,   111,   160,   414,   632,   244,
     152,   604,   154,   152,    22,   245,   153,    22,   633,   194,
      22,   114,   279,   200,   246,   241,   221,   155,   241,  -337,
     284,    79,    51,   510,    22,   280,   158,   665,   425,   605,
     247,   159,   606,   102,   502,   401,   332,   103,   401,   432,
     548,   201,   202,   549,   401,   614,    22,    22,   614,   100,
     406,   401,   291,   263,   610,   249,   194,   264,   477,   265,
     634,   333,   203,   371,   583,   372,   252,    22,   669,  -350,
    -350,   253,   158,   102,   401,   742,   666,   103,   741,   401,
     240,   401,   347,   336,   658,   506,   347,    22,   507,   335,
     732,    22,   324,   401,   337,    77,    82,   194,   194,   401,
     338,   478,   194,    28,   242,   353,   194,   623,   622,   490,
     612,    22,   612,   378,   378,   401,    77,   147,    29,   615,
     667,   401,   362,   363,   364,   401,   739,   394,   409,   395,
     640,   413,   401,   396,   325,   397,   398,   617,   399,   400,
      77,   561,   294,    22,   243,  -337,   150,    22,   151,   244,
     394,   491,   395,   414,    22,   245,   396,   368,   397,   398,
     480,   399,   400,    28,   246,   401,   201,   202,    22,   204,
      51,   401,   641,    22,   243,   152,   612,   401,    29,   244,
     247,   578,   427,   222,    22,   245,   649,   203,    22,   315,
     495,   391,   409,   380,   246,   316,   453,   241,   435,   654,
     401,   156,   -60,   263,   464,   249,   150,   264,   151,   265,
     247,   219,   401,    22,    22,   737,   252,   424,   222,   341,
     342,   253,   343,    28,   194,   738,   697,   727,   401,   258,
     291,   148,   760,   263,   401,   249,   381,   264,    29,   265,
      22,   401,   498,   262,    22,   500,   252,   498,   378,   468,
      22,   253,   149,   748,   461,   632,   466,   756,    22,   661,
     469,   470,   471,   763,    22,   633,   150,   401,   151,    78,
      81,   766,   476,   267,   736,   740,   479,   627,   482,   761,
     281,   628,   401,   401,   492,   146,   493,   401,   288,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,   296,   547,   514,   317,
     550,   392,   515,   418,   516,   318,   197,   393,    51,   419,
      29,   282,   475,   483,   556,   519,   152,   194,   316,   484,
     194,    31,   682,   508,   509,   143,   194,   409,   683,   573,
      22,    79,   344,   297,    34,    35,   552,    22,    59,   322,
      38,    22,    39,   562,    40,   655,   453,   453,    22,   566,
      22,   140,   567,   551,   319,   485,    41,   326,   316,   486,
     591,   320,   594,   321,   299,   596,   584,   585,   205,   206,
     207,   208,   209,   210,   211,   212,   607,   300,   139,   608,
       1,     2,     3,   625,   626,   564,   194,   194,   565,   301,
     413,   618,   591,   620,   302,   354,   355,   356,   357,   358,
     359,   360,   361,    83,    85,   576,   303,   421,   577,   422,
       7,     8,     9,    10,    11,   340,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   347,   213,   214,   215,   724,   216,   217,
     218,   365,   366,   367,   464,   323,   487,    29,   488,   503,
     304,   504,   415,   194,   305,   306,   307,    30,    31,   308,
      32,   638,    33,   309,   194,   311,    79,   312,   416,   417,
     420,    34,    35,    36,   313,    37,   423,    38,   314,    39,
     428,    40,   429,   434,   474,   460,   456,  -240,   754,   489,
     203,   494,   496,    41,   505,   527,   645,   401,   646,   511,
     512,   536,   537,   538,   539,   546,   648,   568,   651,   569,
     570,   571,   574,   572,   702,   581,   584,   585,   706,   152,
     582,    55,    69,   580,   588,    73,    74,    76,    80,    80,
      84,    86,   624,   639,   631,   642,   453,   453,   715,   643,
     647,   652,   653,   659,   662,   663,   664,   668,   670,   101,
     107,   686,   694,   684,   695,   113,   689,   690,   691,   101,
     144,   699,   693,    55,   700,   701,   704,   470,   471,   720,
     705,   707,   717,   719,   369,   157,   721,   696,   730,   243,
     198,   198,   750,   746,   244,   751,   769,   611,   677,    22,
     245,   679,   220,    55,   407,   680,   535,   375,    80,   246,
     426,    80,   257,   681,   261,   459,   272,   644,   722,   433,
     557,   687,   716,   692,   718,   247,   374,   382,     0,     0,
     513,     0,   198,   278,     0,   726,     0,     0,     0,     0,
       0,   287,     0,     0,   295,     0,     0,     0,   263,   376,
     249,   101,   264,     0,   265,   743,     0,   744,   745,     0,
       0,   252,     0,     0,     0,   747,   253,     0,     0,     0,
      87,    88,    89,    90,    91,    92,    93,   272,   272,   198,
       0,     0,     0,    94,     0,   101,   755,   339,    22,     0,
       0,     0,     0,     0,   762,     0,     0,     0,    95,     0,
       0,   765,     0,     0,   768,     0,     0,   770,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     198,   198,   278,   345,    96,   198,     0,     0,     0,   198,
       0,     0,     0,     0,     0,    97,    98,     0,     0,     0,
       0,     0,   467,     0,     0,     0,     0,    99,     0,     0,
       0,    55,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     272,     0,   272,     0,     0,     0,   373,    76,   272,   272,
     386,   389,   390,     0,     0,     0,     0,   272,   404,     0,
      80,     0,   408,   272,   410,   411,   272,     0,     0,    87,
      88,    89,    90,    91,    92,    93,     0,     0,     0,     0,
     107,     0,    94,     0,     0,   287,     0,    22,     0,   454,
     455,     0,   295,     0,     0,     0,     0,    95,     0,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,     0,   198,     0,     0,
       0,   101,     0,    96,     0,     0,    56,   257,     0,     0,
      29,     0,     0,     0,    97,    98,     0,     0,     0,   481,
      30,    31,     0,    32,     0,    33,    99,     0,     0,     0,
      58,     0,     0,     0,    34,    35,    36,     0,    59,   310,
      38,     0,    39,     0,    40,     0,     0,     0,     0,    55,
       0,     0,     0,     0,     0,     0,    41,   272,     0,     0,
     272,     0,   272,   272,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   257,     0,   272,   272,   101,   272,   272,
     272,   272,   272,   256,   261,     0,   533,   534,   272,     0,
       0,     0,     0,     0,   272,   272,   272,   272,     0,     0,
     198,   243,   278,   198,     0,     0,   244,     0,   555,   198,
       0,    22,   245,     0,     0,     0,     0,     0,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,     0,   454,
     454,   455,   563,     0,     0,     0,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   272,     0,   272,     0,     0,     0,     0,     0,
     263,   579,   249,   501,   264,     0,   265,     0,   278,   198,
     198,     0,     0,   252,   272,     0,     0,     0,   253,   272,
       0,     0,   272,     0,   590,   272,   272,   272,     0,   595,
     272,   272,     0,     0,   272,   601,   603,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,    80,   233,   234,
     235,   236,   616,     0,     0,   272,   272,   272,   272,   261,
       0,   237,   238,     0,     0,     0,   239,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   198,     0,     0,     0,
     637,     0,   134,     0,     0,     0,     0,   198,     0,   379,
     135,   384,   387,     0,     0,     0,     0,     0,   403,   650,
       0,     0,     0,     0,     0,     0,     0,     0,   657,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   272,   272,   272,   272,   272,     0,
     533,     0,     0,     0,   533,   533,     0,     0,     0,     0,
       0,     0,     0,     0,   685,   243,   555,   688,     0,     0,
     244,     0,     0,     0,     0,    22,   245,     0,     0,   454,
     454,     0,     0,   375,     0,   246,     0,     0,   473,     0,
     698,     0,     0,     0,     0,     0,     0,     0,     0,   272,
     272,   247,     0,   272,     0,   272,   272,   272,   272,   272,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     616,     0,     0,   272,   472,   376,   249,     0,   250,     0,
     251,     0,     0,     0,   723,     0,     0,   252,   728,   272,
       0,   272,   253,     0,   272,   272,     0,   272,     0,     0,
       0,     0,     0,     0,   256,     0,   517,   518,     0,   520,
     521,   522,   524,   525,     0,     0,     0,     0,   749,     0,
       0,     0,     0,     0,     0,   542,   543,   544,   545,   272,
       0,   272,   243,     0,     0,     0,     0,   244,     0,   757,
     272,   272,    22,   245,     0,     0,     0,   764,     0,     0,
       0,     0,   246,     0,   767,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   247,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   379,     0,     0,     0,     0,     0,     0,
       0,   263,   497,   249,     0,   264,     0,   265,     0,     0,
       0,     0,     0,     0,   252,   586,     0,     0,     0,   253,
     587,     0,     0,   589,     0,     0,   592,   593,     0,     0,
       0,   597,   598,     0,     0,   599,   600,   602,     5,     6,
       0,     7,     8,     9,    10,    11,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    31,
       0,    32,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,    34,    35,    36,     0,    37,     0,    38,     0,
      39,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,   671,   672,   673,   674,   675,
       0,     0,     0,     0,     0,     0,   177,   178,   179,   180,
     181,   182,   183,   184,     0,   185,    22,   186,   187,    25,
     188,   189,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    56,
       0,   703,     0,    29,     0,     0,   708,   709,   710,   711,
     712,   713,    57,    30,    31,   190,    32,   191,    33,   192,
       0,   193,     0,    58,     0,     0,     0,    34,    35,    36,
       0,    59,     0,    38,     0,    39,     0,    40,     0,     0,
     729,     0,   731,     0,   629,   733,   734,     0,   735,    41,
       0,   177,   178,   179,   180,   181,   182,   183,   184,     0,
     185,    22,   186,   187,    25,   188,   189,     0,     0,   630,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     752,     0,   753,     0,     0,     0,     0,     0,     0,     0,
       0,   758,   759,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
     190,     0,   191,     0,   192,     0,   193,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    30,    31,     0,    32,     0,    33,
       0,     0,   131,   132,    58,     0,     0,   133,    34,    35,
      36,     0,    59,     0,    38,     0,    39,     0,    40,     0,
       0,    60,    61,   134,     0,     0,     0,     0,     0,     0,
      41,   135,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,   161,   162,   163,
     164,   165,   166,    29,   167,   168,   169,   125,   170,   171,
     172,   173,   130,    30,    31,     0,    32,     0,    33,     0,
       0,   174,   175,    58,     0,     0,   176,    34,    35,    36,
       0,    59,     0,    38,     0,    39,     0,    40,     0,     0,
      60,    61,     0,     0,     0,     0,     0,     0,     0,    41,
     436,   437,   438,   439,   440,   441,   442,   443,    20,   444,
      22,   445,   446,    25,   447,   448,    28,     0,     0,     0,
       0,     0,     0,     0,     0,   161,   162,   163,   164,   165,
     166,    29,   167,   168,   169,   125,   170,   171,   172,   173,
     130,    30,    31,     0,    32,     0,    33,     0,     0,   174,
     175,    58,     0,     0,   176,    34,    35,    36,     0,   449,
       0,   450,     0,   451,     0,   452,     0,     0,    60,    61,
       0,     0,     0,     0,     0,     0,     0,    41,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    30,
      31,     0,    32,     0,    33,     0,     0,     0,     0,    58,
       0,     0,     0,    34,    35,    36,   457,   289,     0,    38,
       0,   290,   458,    40,     0,     0,    60,    61,     0,     0,
       0,     0,     0,     0,     0,    41,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,     0,   334,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,     0,    29,     0,     0,
       0,     0,     0,     0,   243,     0,    57,    30,    31,   244,
      32,     0,    33,     0,    22,   245,     0,    58,     0,     0,
       0,    34,    35,    36,   246,    59,     0,    38,     0,    39,
       0,    40,     0,     0,    60,    61,     0,     0,     0,     0,
     247,     0,     0,    41,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     0,     0,   383,     0,   249,     0,   264,     0,   265,
       0,    56,     0,     0,     0,    29,   252,     0,     0,   523,
       0,   253,   243,     0,    57,    30,    31,   244,    32,     0,
      33,     0,    22,   245,     0,    58,     0,     0,     0,    34,
      35,    36,   246,    59,     0,    38,   465,    39,     0,    40,
       0,     0,    60,    61,     0,     0,     0,     0,   247,     0,
       0,    41,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,   248,     0,   249,     0,   250,     0,   251,     0,    56,
       0,     0,     0,    29,   252,     0,     0,     0,     0,   253,
     243,     0,    57,    30,    31,   244,    32,     0,    33,     0,
      22,   245,     0,    58,     0,     0,     0,    34,    35,    36,
     246,    59,     0,    38,   575,    39,     0,    40,     0,     0,
      60,    61,     0,     0,     0,     0,   247,     0,     0,    41,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,     0,   263,
       0,   249,     0,   264,     0,   265,     0,    56,     0,     0,
       0,    29,   252,     0,     0,     0,     0,   253,   243,     0,
      57,    30,    31,   244,    32,     0,    33,     0,    22,   245,
       0,    58,     0,     0,     0,    34,    35,    36,   246,    59,
       0,    38,     0,    39,     0,    40,     0,     0,    60,    61,
       0,     0,     0,     0,   247,     0,     0,    41,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     0,     0,   327,     0,   249,
       0,   264,     0,   265,     0,    56,     0,     0,     0,    29,
     252,     0,     0,     0,     0,   253,   243,     0,    57,    30,
      31,   244,    32,     0,    33,     0,    22,   245,     0,    58,
       0,     0,     0,    34,    35,    36,   246,   289,     0,    38,
       0,   290,     0,    40,     0,     0,    60,    61,     0,     0,
       0,     0,   247,     0,     0,    41,   436,   437,   438,   439,
     440,   441,   442,   443,    20,   444,    22,   445,   446,    25,
     447,   448,    28,     0,     0,   383,     0,   249,     0,   264,
       0,   265,     0,    56,     0,     0,     0,    29,   252,     0,
       0,     0,     0,   253,     0,     0,    57,    30,    31,     0,
      32,     0,    33,     0,     0,     0,     0,    58,     0,     0,
       0,    34,    35,    36,     0,   449,     0,   450,     0,   451,
       0,   452,     0,     0,    60,    61,     0,     0,     0,     0,
       0,     0,     0,    41,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,     0,    32,     0,
      33,     0,     0,     0,     0,    58,     0,     0,     0,    34,
      35,    36,     0,    59,     0,    38,     0,    39,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    56,
       0,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,    32,     0,    33,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,    36,
       0,    59,   298,    38,     0,    39,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,     0,
       0,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    32,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,    36,     0,    59,
       0,    38,     0,    39,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,    32,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,     0,    59,     0,    38,
       0,    39,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,   177,
     178,   179,   180,   181,   182,   183,   184,    29,   185,    22,
     186,   187,    25,   188,   189,     0,     0,     0,    31,     0,
       0,     0,     0,   283,     0,     0,     0,     0,     0,     0,
     346,    34,    35,     0,     0,    59,     0,    38,     0,    39,
       0,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,   190,     0,
     191,     0,   192,     0,   193,   177,   178,   179,   180,   181,
     182,   183,   184,     0,   185,    22,   186,   187,    25,   188,
     189,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   348,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   190,     0,   191,     0,   192,     0,
     193
};

static const yytype_int16 yycheck[] =
{
       2,     3,    32,    52,    34,     8,     9,    60,    61,    38,
       1,    86,   200,   201,   202,   203,    61,    29,    57,    43,
     190,   191,   528,   192,   114,    56,   540,    60,    61,    31,
     609,   148,     8,   404,   613,     8,    38,   422,     8,    41,
      33,     0,     8,    33,    25,    25,    25,     8,    41,    33,
      43,    41,    43,    43,    15,    78,    58,    41,    16,    20,
     109,    38,    31,   112,    25,    26,    28,    25,    26,   102,
      25,    78,    69,    36,    35,    78,     8,    46,    81,    33,
     110,    84,    73,    34,    25,    82,   117,    41,    69,    36,
      51,   130,    39,    74,    43,    88,   149,    78,    88,    79,
      79,    64,    65,   488,    88,    81,    25,    25,    81,   121,
      80,    88,   114,    74,    80,    76,   149,    78,    34,    80,
      78,   150,    85,   240,    79,   242,    87,    25,    41,    80,
      81,    92,   163,    74,    88,   714,    43,    78,    41,    88,
      38,    88,   195,   155,    79,    41,   199,    25,    44,   151,
      79,    25,    38,    88,   156,    74,    74,   190,   191,    88,
      38,    77,   195,    31,    38,   204,   199,   681,   539,    38,
     676,    25,   678,   248,   249,    88,    74,    39,    46,    33,
      43,    88,   213,   214,   215,    88,    43,    38,   263,    40,
      38,   266,    88,    44,    80,    46,    47,     8,    49,    50,
      74,    69,   292,    25,    15,    33,    74,    25,    76,    20,
      38,    80,    40,    41,    25,    26,    44,   219,    46,    47,
      38,    49,    50,    31,    35,    88,    64,    65,    25,    69,
     221,    88,    80,    25,    15,   284,   742,    88,    46,    20,
      51,    38,   281,    46,    25,    26,    38,    85,    25,    75,
      53,   253,   327,    34,    35,    81,   289,   260,   288,    75,
      88,    38,    39,    74,   317,    76,    74,    78,    76,    80,
      51,    38,    88,    25,    25,    75,    87,   279,    46,   449,
     450,    92,   451,    31,   317,    79,    38,    38,    88,    32,
     292,    39,    79,    74,    88,    76,    77,    78,    46,    80,
      25,    88,   377,    32,    25,   380,    87,   382,   383,   321,
      25,    92,    60,    38,   316,    16,   318,    38,    25,    80,
     322,   323,   324,    38,    25,    26,    74,    88,    76,     8,
       9,    38,   334,   408,    80,    80,   338,    34,   340,    80,
      38,    38,    88,    88,   346,   369,   348,    88,    38,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    75,   420,    74,    80,
     423,    75,    78,    75,    80,    86,   429,    81,   369,    81,
      46,    63,    75,    75,   429,   397,   435,   420,    81,    81,
     423,    57,    75,    80,    81,    20,   429,   472,    81,   474,
      25,   404,    20,    75,    70,    71,    20,    25,    74,    38,
      76,    25,    78,    20,    80,    20,   449,   450,    25,    77,
      25,   450,    80,   425,    77,    77,    92,    92,    81,    81,
     505,    79,   507,    81,    75,   510,   489,   490,    47,    48,
      49,    50,    51,    52,    53,    54,    36,    75,   450,    39,
       3,     4,     5,    80,    81,   457,   489,   490,   460,    75,
     535,   536,   537,   538,    75,   205,   206,   207,   208,   209,
     210,   211,   212,    10,    11,   477,    75,    79,   480,    81,
       9,    10,    11,    12,    13,    67,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,   556,    40,    41,    42,   695,    43,    44,
      45,   216,   217,   218,   567,    38,    79,    46,    81,    79,
      75,    81,    33,   556,    75,    75,    75,    56,    57,    75,
      59,   561,    61,    75,   567,    75,   539,    75,    43,    41,
      81,    70,    71,    72,    75,    74,    38,    76,    75,    78,
      80,    80,    80,    37,    32,    38,    82,    38,   746,    38,
      85,    46,    75,    92,    34,    14,   568,    88,   570,    46,
      92,    81,    34,    34,    14,    75,   578,    36,   580,    77,
      38,    80,    77,    80,   659,    75,   639,   640,   663,   638,
      77,     1,     2,    68,    80,     5,     6,     7,     8,     9,
      10,    11,    34,    38,    80,    79,   639,   640,   683,    82,
      77,    80,    80,    34,    80,    34,    80,    34,    34,    29,
      30,    58,    34,    38,    81,    35,   628,   629,   630,    39,
      40,    38,   634,    43,    34,    38,    38,   639,   640,    33,
      39,    39,    38,    38,   221,    55,    79,   649,    77,    15,
      60,    61,    38,    81,    20,    38,    38,   527,   610,    25,
      26,   614,    73,    73,   261,   615,   408,    33,    78,    35,
     280,    81,    82,   617,    84,   292,    86,   567,   694,   285,
     430,   626,   684,   631,   686,    51,   247,   249,    -1,    -1,
     393,    -1,   102,   103,    -1,   697,    -1,    -1,    -1,    -1,
      -1,   111,    -1,    -1,   114,    -1,    -1,    -1,    74,    75,
      76,   121,    78,    -1,    80,   717,    -1,   719,   720,    -1,
      -1,    87,    -1,    -1,    -1,   727,    92,    -1,    -1,    -1,
       7,     8,     9,    10,    11,    12,    13,   147,   148,   149,
      -1,    -1,    -1,    20,    -1,   155,   748,   157,    25,    -1,
      -1,    -1,    -1,    -1,   756,    -1,    -1,    -1,    35,    -1,
      -1,   763,    -1,    -1,   766,    -1,    -1,   769,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,   192,   193,    61,   195,    -1,    -1,    -1,   199,
      -1,    -1,    -1,    -1,    -1,    72,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,   221,   222,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     240,    -1,   242,    -1,    -1,    -1,   246,   247,   248,   249,
     250,   251,   252,    -1,    -1,    -1,    -1,   257,   258,    -1,
     260,    -1,   262,   263,   264,   265,   266,    -1,    -1,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
     280,    -1,    20,    -1,    -1,   285,    -1,    25,    -1,   289,
     290,    -1,   292,    -1,    -1,    -1,    -1,    35,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,   317,    -1,    -1,
      -1,   321,    -1,    61,    -1,    -1,    42,   327,    -1,    -1,
      46,    -1,    -1,    -1,    72,    73,    -1,    -1,    -1,   339,
      56,    57,    -1,    59,    -1,    61,    84,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    70,    71,    72,    -1,    74,    75,
      76,    -1,    78,    -1,    80,    -1,    -1,    -1,    -1,   369,
      -1,    -1,    -1,    -1,    -1,    -1,    92,   377,    -1,    -1,
     380,    -1,   382,   383,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   393,    -1,   395,   396,   397,   398,   399,
     400,   401,   402,    82,   404,    -1,   406,   407,   408,    -1,
      -1,    -1,    -1,    -1,   414,   415,   416,   417,    -1,    -1,
     420,    15,   422,   423,    -1,    -1,    20,    -1,   428,   429,
      -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   449,
     450,   451,   452,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   472,    -1,   474,    -1,    -1,    -1,    -1,    -1,
      74,   481,    76,    77,    78,    -1,    80,    -1,   488,   489,
     490,    -1,    -1,    87,   494,    -1,    -1,    -1,    92,   499,
      -1,    -1,   502,    -1,   504,   505,   506,   507,    -1,   509,
     510,   511,    -1,    -1,   514,   515,   516,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   527,    51,    52,
      53,    54,   532,    -1,    -1,   535,   536,   537,   538,   539,
      -1,    64,    65,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   556,    -1,    -1,    -1,
     560,    -1,    85,    -1,    -1,    -1,    -1,   567,    -1,   248,
      93,   250,   251,    -1,    -1,    -1,    -1,    -1,   257,   579,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   588,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   604,   605,   606,   607,   608,    -1,
     610,    -1,    -1,    -1,   614,   615,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   624,    15,   626,   627,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,   639,
     640,    -1,    -1,    33,    -1,    35,    -1,    -1,   327,    -1,
     650,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   659,
     660,    51,    -1,   663,    -1,   665,   666,   667,   668,   669,
     670,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     680,    -1,    -1,   683,    74,    75,    76,    -1,    78,    -1,
      80,    -1,    -1,    -1,   694,    -1,    -1,    87,   698,   699,
      -1,   701,    92,    -1,   704,   705,    -1,   707,    -1,    -1,
      -1,    -1,    -1,    -1,   393,    -1,   395,   396,    -1,   398,
     399,   400,   401,   402,    -1,    -1,    -1,    -1,   728,    -1,
      -1,    -1,    -1,    -1,    -1,   414,   415,   416,   417,   739,
      -1,   741,    15,    -1,    -1,    -1,    -1,    20,    -1,   749,
     750,   751,    25,    26,    -1,    -1,    -1,   757,    -1,    -1,
      -1,    -1,    35,    -1,   764,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   472,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    78,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    87,   494,    -1,    -1,    -1,    92,
     499,    -1,    -1,   502,    -1,    -1,   505,   506,    -1,    -1,
      -1,   510,   511,    -1,    -1,   514,   515,   516,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    -1,    74,    -1,    76,    -1,
      78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    92,   604,   605,   606,   607,   608,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,   660,    -1,    46,    -1,    -1,   665,   666,   667,   668,
     669,   670,    55,    56,    57,    74,    59,    76,    61,    78,
      -1,    80,    -1,    66,    -1,    -1,    -1,    70,    71,    72,
      -1,    74,    -1,    76,    -1,    78,    -1,    80,    -1,    -1,
     699,    -1,   701,    -1,     8,   704,   705,    -1,   707,    92,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     739,    -1,   741,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   750,   751,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      74,    -1,    76,    -1,    78,    -1,    80,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    -1,    61,
      -1,    -1,    64,    65,    66,    -1,    -1,    69,    70,    71,
      72,    -1,    74,    -1,    76,    -1,    78,    -1,    80,    -1,
      -1,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    93,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    -1,    61,    -1,
      -1,    64,    65,    66,    -1,    -1,    69,    70,    71,    72,
      -1,    74,    -1,    76,    -1,    78,    -1,    80,    -1,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    -1,    61,    -1,    -1,    64,
      65,    66,    -1,    -1,    69,    70,    71,    72,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    -1,    -1,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    -1,    76,
      -1,    78,    79,    80,    -1,    -1,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    -1,    55,    56,    57,    20,
      59,    -1,    61,    -1,    25,    26,    -1,    66,    -1,    -1,
      -1,    70,    71,    72,    35,    74,    -1,    76,    -1,    78,
      -1,    80,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    92,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    74,    -1,    76,    -1,    78,    -1,    80,
      -1,    42,    -1,    -1,    -1,    46,    87,    -1,    -1,    90,
      -1,    92,    15,    -1,    55,    56,    57,    20,    59,    -1,
      61,    -1,    25,    26,    -1,    66,    -1,    -1,    -1,    70,
      71,    72,    35,    74,    -1,    76,    77,    78,    -1,    80,
      -1,    -1,    83,    84,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    92,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    74,    -1,    76,    -1,    78,    -1,    80,    -1,    42,
      -1,    -1,    -1,    46,    87,    -1,    -1,    -1,    -1,    92,
      15,    -1,    55,    56,    57,    20,    59,    -1,    61,    -1,
      25,    26,    -1,    66,    -1,    -1,    -1,    70,    71,    72,
      35,    74,    -1,    76,    77,    78,    -1,    80,    -1,    -1,
      83,    84,    -1,    -1,    -1,    -1,    51,    -1,    -1,    92,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    -1,    42,    -1,    -1,
      -1,    46,    87,    -1,    -1,    -1,    -1,    92,    15,    -1,
      55,    56,    57,    20,    59,    -1,    61,    -1,    25,    26,
      -1,    66,    -1,    -1,    -1,    70,    71,    72,    35,    74,
      -1,    76,    -1,    78,    -1,    80,    -1,    -1,    83,    84,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    92,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    74,    -1,    76,
      -1,    78,    -1,    80,    -1,    42,    -1,    -1,    -1,    46,
      87,    -1,    -1,    -1,    -1,    92,    15,    -1,    55,    56,
      57,    20,    59,    -1,    61,    -1,    25,    26,    -1,    66,
      -1,    -1,    -1,    70,    71,    72,    35,    74,    -1,    76,
      -1,    78,    -1,    80,    -1,    -1,    83,    84,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    92,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    74,    -1,    76,    -1,    78,
      -1,    80,    -1,    42,    -1,    -1,    -1,    46,    87,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    55,    56,    57,    -1,
      59,    -1,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    70,    71,    72,    -1,    74,    -1,    76,    -1,    78,
      -1,    80,    -1,    -1,    83,    84,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    59,    -1,
      61,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    70,
      71,    72,    -1,    74,    -1,    76,    -1,    78,    -1,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    92,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    59,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      -1,    74,    75,    76,    -1,    78,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    -1,    59,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,    74,
      -1,    76,    -1,    78,    -1,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    -1,    59,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    -1,    74,    -1,    76,
      -1,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    46,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    70,    71,    -1,    -1,    74,    -1,    76,    -1,    78,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    -1,    -1,    74,    -1,
      76,    -1,    78,    -1,    80,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    76,    -1,    78,    -1,
      80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    95,     6,     7,     9,    10,    11,
      12,    13,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    46,
      56,    57,    59,    61,    70,    71,    72,    74,    76,    78,
      80,    92,    96,    97,    98,    99,   100,   101,   103,   108,
     113,   123,   131,   139,   153,   173,    42,    55,    66,    74,
      83,    84,   117,   118,   119,   120,   121,   122,   123,   173,
     117,   173,     0,   173,   173,   166,   173,    74,   112,   113,
     173,   112,    74,   158,   173,   158,   173,     7,     8,     9,
      10,    11,    12,    13,    20,    35,    61,    72,    73,    84,
     152,   173,    74,    78,   124,   125,   145,   173,   117,   131,
     140,    78,   131,   173,    78,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    64,    65,    69,    85,    93,   114,   117,   156,   117,
     156,   151,   152,    20,   173,   117,    98,    39,    39,    60,
      74,    76,   153,    28,    31,    46,    38,   173,   121,   119,
     117,    40,    41,    42,    43,    44,    45,    47,    48,    49,
      51,    52,    53,    54,    64,    65,    69,    15,    16,    17,
      18,    19,    20,    21,    22,    24,    26,    27,    29,    30,
      74,    76,    78,    80,   139,   143,   144,   146,   173,   143,
      36,    64,    65,    85,    69,    47,    48,    49,    50,    51,
      52,    53,    54,    40,    41,    42,    43,    44,    45,    38,
      96,     8,    46,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    51,    52,    53,    54,    64,    65,    69,
      38,   113,    38,    15,    20,    26,    35,    51,    74,    76,
      78,    80,    87,    92,   159,   160,   164,   173,    32,   111,
     112,   173,    32,    74,    78,    80,   116,   163,   164,   167,
     169,   170,   173,   146,   147,   148,   149,   150,   173,    69,
      82,    38,    63,    62,   131,   132,   133,   173,    38,    74,
      78,   117,   126,   127,   145,   173,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    81,    80,    86,    77,
      79,    81,    38,    38,    38,    80,    92,    74,   157,   158,
     163,   157,   146,   156,    34,   117,   152,   117,    38,   173,
      67,   147,   147,   149,    20,   173,    46,   146,    46,   118,
     118,   118,   118,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   122,   122,   122,   117,    97,
     173,   157,   157,   173,   166,    33,    75,   162,   163,   164,
      34,    77,   162,    74,   164,   171,   173,   164,   172,   173,
     173,   117,    75,    81,    38,    40,    44,    46,    47,    49,
      50,    88,   161,   164,   173,     8,    80,   114,   173,   163,
     173,   173,     8,   163,    41,    33,    43,    41,    75,    81,
      81,    79,    81,    38,   117,    69,   125,   119,    80,    80,
     141,   142,    79,   133,    37,   131,    15,    16,    17,    18,
      19,    20,    21,    22,    24,    26,    27,    29,    30,    74,
      76,    78,    80,   139,   173,   173,    82,    73,    79,   127,
      38,   117,   129,   130,   146,    77,   117,    79,   152,   117,
     117,   117,    74,   164,    32,    75,   117,    34,    77,   117,
      38,   173,   117,    75,    81,    77,    81,    79,    81,    38,
      38,    80,   117,   117,    46,    53,    75,    75,   163,    43,
     163,    77,    43,    79,    81,    34,    41,    44,    80,    81,
      34,    46,    92,   160,    74,    78,    80,   164,   164,   152,
     164,   164,   164,    90,   164,   164,   111,    14,   106,   107,
     104,   105,   115,   173,   173,   116,    81,    34,    34,    14,
     109,   110,   164,   164,   164,   164,    75,   146,    79,   150,
     146,   117,    20,   154,   155,   173,   143,   142,   134,   135,
     136,    69,    20,   173,   117,   117,    77,    80,    36,    77,
      38,    80,    80,   163,    77,    77,   117,   117,    38,   173,
      68,    75,    77,    79,   146,   146,   164,   164,    80,   164,
     173,   163,   164,   164,   163,   173,   163,   164,   164,   164,
     164,   173,   164,   173,    38,    36,    39,    36,    39,     8,
      80,   101,   107,     8,    81,    33,   173,     8,   163,   168,
     163,   102,   111,   110,    34,    80,    81,    34,    38,     8,
      33,    80,    16,    26,    78,   137,   138,   173,   131,    38,
      38,    80,    79,    82,   129,   117,   117,    77,   117,    38,
     173,   117,    80,    80,    75,    20,   165,   173,    79,    34,
      43,    80,    80,    34,    80,    41,    43,    43,    34,    41,
      34,   164,   164,   164,   164,   164,   106,   104,   106,   105,
     115,   109,    75,    81,    38,   173,    58,   155,   173,   117,
     117,   117,   135,   117,    34,    81,   117,    38,   173,    38,
      34,    38,   163,   164,    38,    39,   163,    39,   164,   164,
     164,   164,   164,   164,     8,   163,   117,    38,   117,    38,
      33,    79,   138,   173,   118,   128,   117,    38,   173,   164,
      77,   164,    79,   164,   164,   164,    80,    75,    79,    43,
      80,    41,   106,   117,   117,   117,    81,   117,    38,   173,
      38,    38,   164,   164,   118,   117,    38,   173,   164,   164,
      79,    80,   117,    38,   173,   117,    38,   173,   117,    38,
     117
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    95,    96,    96,    96,    97,
      97,    97,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      99,   100,   100,   101,   102,   103,   103,   103,   103,   103,
     103,   103,   103,   104,   104,   105,   106,   106,   107,   108,
     108,   108,   108,   109,   109,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   116,   116,   117,   117,   117,   117,   118,
     118,   118,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   121,   121,   121,   121,
     121,   122,   122,   122,   122,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   132,   132,   133,   134,   134,   135,   136,
     136,   137,   137,   138,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   143,   143,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     145,   145,   145,   145,   145,   146,   147,   147,   148,   148,
     149,   149,   150,   151,   151,   151,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   153,   153,   153,   154,   154,   155,   155,   155,   156,
     156,   156,   157,   157,   158,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   161,   161,
     162,   162,   163,   163,   163,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   165,   165,   166,   166,   167,   167,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   172,   172,
     172,   173
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     4,     2,     2,     3,     4,     1,     0,
       1,     2,     1,     1,     1,     1,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,     1,
       2,     4,     4,     3,     3,     5,     7,     7,     9,     3,
       5,     5,     7,     1,     3,     3,     1,     2,     2,     3,
       5,     5,     7,     1,     2,     2,     1,     3,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     4,     4,     3,     1,     2,
       3,     3,     3,     3,     1,     6,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     2,
       1,     3,     3,     3,     1,     1,     4,     5,     4,     3,
       4,     4,     6,     3,     3,     1,     3,     2,     1,     4,
       2,     3,     1,     5,     3,     3,     1,     4,     1,     5,
       4,     5,     3,     4,     6,     5,     5,     5,     5,     3,
       6,     8,     3,     4,     2,     1,     1,     2,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     3,     3,     1,     4,     2,
       0,     3,     1,     1,     1,     1,     1,     2,     2,     1,
       2,     1,     4,     6,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     5,     5,     3,     4,     3,     4,     1,
       1,     3,     4,     3,     4,     1,     1,     0,     3,     1,
       3,     1,     3,     0,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     1,     1,     3,     3,     5,     5,     0,
       1,     3,     3,     1,     3,     1,     3,     2,     3,     3,
       3,     7,     9,     7,     7,     9,     7,     5,     5,     5,
       5,     7,     7,     9,     9,     7,     7,     5,     1,     2,
       2,     1,     3,     1,     1,     1,     3,     2,     3,     7,
       3,     3,     3,     3,     2,     1,     1,     4,     3,     3,
       4,     1,     3,     1,     1,     1,     3,     1,     5,     1,
       3,     1,     3,     3,     3,     5,     3,     5,     3,     3,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 473 "hexpr.y" /* yacc.c:1652  */
    { yyParsedModule = (yyvsp[0].module);                     }
#line 2679 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 3:
#line 474 "hexpr.y" /* yacc.c:1652  */
    { yyParsedVar    = *(yyvsp[-2].string); yyParsedExpr = (yyvsp[0].exp); }
#line 2685 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 4:
#line 475 "hexpr.y" /* yacc.c:1652  */
    { yyParsedVar    = "";  yyParsedExpr = (yyvsp[0].exp); }
#line 2691 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 5:
#line 476 "hexpr.y" /* yacc.c:1652  */
    { yyParsedExpr   = (yyvsp[0].exp);                     }
#line 2697 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 6:
#line 479 "hexpr.y" /* yacc.c:1652  */
    { (yyval.module) = (yyvsp[0].module); (yyval.module)->setOption(*(yyvsp[-1].string), m((yylsp[-2]))); }
#line 2703 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 7:
#line 480 "hexpr.y" /* yacc.c:1652  */
    { (yyval.module) = new Module(*(yyvsp[-2].string), *(yyvsp[0].mdefs)); }
#line 2709 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 8:
#line 481 "hexpr.y" /* yacc.c:1652  */
    { (yyval.module) = new Module(freshName(), *(yyvsp[0].mdefs)); }
#line 2715 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 9:
#line 483 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdefs) = autorelease(new ModuleDefs()); }
#line 2721 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 10:
#line 484 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdefs) = autorelease(new ModuleDefs()); (yyval.mdefs)->push_back(ModuleDefPtr((yyvsp[0].mdef))); }
#line 2727 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 11:
#line 485 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdefs) = (yyvsp[-1].mdefs);                            (yyval.mdefs)->push_back(ModuleDefPtr((yyvsp[0].mdef))); }
#line 2733 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 12:
#line 487 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = (yyvsp[0].mdef); }
#line 2739 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 13:
#line 488 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = (yyvsp[0].mdef); }
#line 2745 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 14:
#line 489 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = (yyvsp[0].mvtydef); }
#line 2751 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 15:
#line 490 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = (yyvsp[0].mdef); }
#line 2757 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 16:
#line 491 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = (yyvsp[0].mdef); }
#line 2763 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 17:
#line 493 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-2]), (yylsp[0]))); }
#line 2769 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 18:
#line 494 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-3]), (yylsp[0]))); }
#line 2775 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 19:
#line 495 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-4]), (yylsp[0]))); }
#line 2781 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 20:
#line 496 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-5]), (yylsp[0]))); }
#line 2787 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 21:
#line 497 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-6]), (yylsp[0]))); }
#line 2793 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 22:
#line 498 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-7]), (yylsp[0]))); }
#line 2799 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 23:
#line 499 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-8]), (yylsp[0]))); }
#line 2805 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 24:
#line 500 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-9].string), *(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-9]), (yylsp[0]))); }
#line 2811 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 25:
#line 501 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-10].string), *(yyvsp[-9].string), *(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-10]), (yylsp[0]))); }
#line 2817 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 26:
#line 502 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-11].string), *(yyvsp[-10].string), *(yyvsp[-9].string), *(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-11]), (yylsp[0]))); }
#line 2823 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 27:
#line 503 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-12].string), *(yyvsp[-11].string), *(yyvsp[-10].string), *(yyvsp[-9].string), *(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-12]), (yylsp[0]))); }
#line 2829 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 28:
#line 504 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(*(yyvsp[-13].string), *(yyvsp[-12].string), *(yyvsp[-11].string), *(yyvsp[-10].string), *(yyvsp[-9].string), *(yyvsp[-8].string), *(yyvsp[-7].string), *(yyvsp[-6].string), *(yyvsp[-5].string), *(yyvsp[-4].string), *(yyvsp[-3].string), *(yyvsp[-2].string)), ExprPtr((yyvsp[0].exp)), m((yylsp[-13]), (yylsp[0]))); }
#line 2835 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 29:
#line 507 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MVarDef(list(freshName()), let(freshName(), ExprPtr((yyvsp[0].exp)), mktunit(m((yylsp[0]))), m((yylsp[0]))), m((yylsp[0]))); }
#line 2841 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 30:
#line 510 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MImport(yyModulePath, *(yyvsp[0].string), m((yylsp[-1]), (yylsp[0]))); }
#line 2847 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 31:
#line 513 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MTypeDef(MTypeDef::Transparent, hobbes::select(*(yyvsp[-2].strings), 0), hobbes::select(*(yyvsp[-2].strings), 1, (int)(yyvsp[-2].strings)->size()), QualTypePtr((yyvsp[0].qualtype)), m((yylsp[-3]), (yylsp[0]))); }
#line 2853 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 32:
#line 514 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new MTypeDef(MTypeDef::Opaque, hobbes::select(*(yyvsp[-2].strings), 0), hobbes::select(*(yyvsp[-2].strings), 1, (int)(yyvsp[-2].strings)->size()), QualTypePtr((yyvsp[0].qualtype)), m((yylsp[-3]), (yylsp[0]))); }
#line 2859 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 33:
#line 517 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvtydef) = new MVarTypeDef(*(yyvsp[-2].string), QualTypePtr((yyvsp[0].qualtype)), m((yylsp[-2]), (yylsp[0]))); }
#line 2865 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 34:
#line 519 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvdef) = new MVarDef(*(yyvsp[-2].strings), ExprPtr((yyvsp[0].exp)), m((yylsp[-2]), (yylsp[0]))); }
#line 2871 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 35:
#line 522 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(*(yyvsp[-3].tconstraints), *(yyvsp[-1].string), *(yyvsp[0].strings), CFunDepDefs(), MVarTypeDefs(), m((yylsp[-4]), (yylsp[0]))); wantIndent(false); }
#line 2877 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 36:
#line 523 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(*(yyvsp[-5].tconstraints), *(yyvsp[-3].string), *(yyvsp[-2].strings), *(yyvsp[0].fundeps),           MVarTypeDefs(), m((yylsp[-6]), (yylsp[0]))); wantIndent(false); }
#line 2883 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 37:
#line 524 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(*(yyvsp[-5].tconstraints), *(yyvsp[-3].string), *(yyvsp[-2].strings), CFunDepDefs(), *(yyvsp[0].mvtydefs), m((yylsp[-6]), (yylsp[0])));            wantIndent(false); }
#line 2889 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 38:
#line 525 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(*(yyvsp[-7].tconstraints), *(yyvsp[-5].string), *(yyvsp[-4].strings), *(yyvsp[-2].fundeps),           *(yyvsp[0].mvtydefs), m((yylsp[-8]), (yylsp[0])));            wantIndent(false); }
#line 2895 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 39:
#line 526 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(Constraints(), *(yyvsp[-1].string), *(yyvsp[0].strings), CFunDepDefs(), MVarTypeDefs(), m((yylsp[-2]), (yylsp[0]))); wantIndent(false); }
#line 2901 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 40:
#line 527 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(Constraints(), *(yyvsp[-3].string), *(yyvsp[-2].strings), *(yyvsp[0].fundeps),           MVarTypeDefs(), m((yylsp[-4]), (yylsp[0]))); wantIndent(false); }
#line 2907 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 41:
#line 528 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(Constraints(), *(yyvsp[-3].string), *(yyvsp[-2].strings), CFunDepDefs(), *(yyvsp[0].mvtydefs), m((yylsp[-4]), (yylsp[0])));            wantIndent(false); }
#line 2913 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 42:
#line 529 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new ClassDef(Constraints(), *(yyvsp[-5].string), *(yyvsp[-4].strings), *(yyvsp[-2].fundeps),           *(yyvsp[0].mvtydefs), m((yylsp[-6]), (yylsp[0])));            wantIndent(false); }
#line 2919 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 43:
#line 531 "hexpr.y" /* yacc.c:1652  */
    { (yyval.fundeps) = autorelease(new CFunDepDefs()); (yyval.fundeps)->push_back(*(yyvsp[0].fundep)); }
#line 2925 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 44:
#line 532 "hexpr.y" /* yacc.c:1652  */
    { (yyval.fundeps) = (yyvsp[-2].fundeps);                             (yyval.fundeps)->push_back(*(yyvsp[0].fundep)); }
#line 2931 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 45:
#line 534 "hexpr.y" /* yacc.c:1652  */
    { (yyval.fundep) = autorelease(new CFunDepDef(*(yyvsp[-2].strings), *(yyvsp[0].strings))); }
#line 2937 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 46:
#line 536 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvtydefs) = autorelease(new MVarTypeDefs()); (yyval.mvtydefs)->push_back(MVarTypeDefPtr((yyvsp[0].mvtydef))); }
#line 2943 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 47:
#line 537 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvtydefs) = (yyvsp[-1].mvtydefs);                              (yyval.mvtydefs)->push_back(MVarTypeDefPtr((yyvsp[0].mvtydef))); }
#line 2949 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 48:
#line 539 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvtydef) = (yyvsp[0].mvtydef); }
#line 2955 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 49:
#line 542 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new InstanceDef(Constraints(), *(yyvsp[-1].string), *(yyvsp[0].mtypes), MVarDefs(), m((yylsp[-2]), (yylsp[0]))); wantIndent(false); }
#line 2961 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 50:
#line 543 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new InstanceDef(*(yyvsp[-3].tconstraints),           *(yyvsp[-1].string), *(yyvsp[0].mtypes), MVarDefs(), m((yylsp[-4]), (yylsp[0]))); wantIndent(false); }
#line 2967 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 51:
#line 544 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new InstanceDef(Constraints(), *(yyvsp[-3].string), *(yyvsp[-2].mtypes), *(yyvsp[0].mvdefs), m((yylsp[-4]), (yylsp[0])));        wantIndent(false); }
#line 2973 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 52:
#line 545 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mdef) = new InstanceDef(*(yyvsp[-5].tconstraints),           *(yyvsp[-3].string), *(yyvsp[-2].mtypes), *(yyvsp[0].mvdefs), m((yylsp[-6]), (yylsp[0])));        wantIndent(false); }
#line 2979 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 53:
#line 547 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvdefs) = autorelease(new MVarDefs()); (yyval.mvdefs)->push_back(MVarDefPtr((yyvsp[0].mvdef))); }
#line 2985 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 54:
#line 548 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvdefs) = (yyvsp[-1].mvdefs);                          (yyval.mvdefs)->push_back(MVarDefPtr((yyvsp[0].mvdef))); }
#line 2991 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 55:
#line 550 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvdef) = (yyvsp[0].mvdef); }
#line 2997 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 56:
#line 553 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[0].strings); }
#line 3003 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 57:
#line 555 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); (yyval.strings)->push_back(*(yyvsp[-1].string)); (yyval.strings)->push_back(*(yyvsp[-2].string)); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3009 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 58:
#line 557 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3015 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 59:
#line 558 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[-1].strings);                          (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3021 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 60:
#line 560 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 3027 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 61:
#line 562 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 3033 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 62:
#line 564 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("and")); }
#line 3039 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 63:
#line 565 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("or")); }
#line 3045 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 64:
#line 566 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("compose")); }
#line 3051 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 65:
#line 567 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("compose")); }
#line 3057 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 66:
#line 568 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("~")); }
#line 3063 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 67:
#line 569 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("=~")); }
#line 3069 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 68:
#line 570 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("===")); }
#line 3075 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 69:
#line 571 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("==")); }
#line 3081 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 70:
#line 572 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("<")); }
#line 3087 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 71:
#line 573 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("<=")); }
#line 3093 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 72:
#line 574 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string(">")); }
#line 3099 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 73:
#line 575 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string(">=")); }
#line 3105 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 74:
#line 576 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("in")); }
#line 3111 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 75:
#line 577 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("append")); }
#line 3117 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 76:
#line 578 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("+")); }
#line 3123 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 77:
#line 579 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("-")); }
#line 3129 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 78:
#line 580 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("*")); }
#line 3135 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 79:
#line 581 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("/")); }
#line 3141 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 80:
#line 582 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("%")); }
#line 3147 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 81:
#line 584 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3153 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 82:
#line 585 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[-1].strings);                          (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3159 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 83:
#line 587 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 3165 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 84:
#line 588 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = (yyvsp[-1].mtypes);                           (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 3171 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 85:
#line 591 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = makePatternFn(*(yyvsp[-2].patterns), ExprPtr((yyvsp[0].exp)), m((yylsp[-3]), (yylsp[0]))); }
#line 3177 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 86:
#line 592 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = makePatternFn(*(yyvsp[-2].patterns), ExprPtr((yyvsp[0].exp)), m((yylsp[-3]), (yylsp[0]))); }
#line 3183 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 87:
#line 593 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Assign(ExprPtr((yyvsp[-2].exp)), ExprPtr((yyvsp[0].exp)), m((yylsp[-2]), (yylsp[0]))); }
#line 3189 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 88:
#line 594 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3195 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 89:
#line 596 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP1(var("not",m((yylsp[-1]))), (yyvsp[0].exp), m((yylsp[-1]),(yylsp[0]))); }
#line 3201 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 90:
#line 597 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("and",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3207 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 91:
#line 598 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("or",m((yylsp[-1]))),  (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3213 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 92:
#line 599 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("compose",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3219 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 93:
#line 600 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("in",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3225 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 94:
#line 601 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3231 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 95:
#line 603 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP3(var("if",m((yylsp[-5]))), (yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-5]), (yylsp[0]))); }
#line 3237 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 96:
#line 604 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3243 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 97:
#line 606 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("~",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3249 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 98:
#line 607 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("===",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3255 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 99:
#line 608 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("==",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3261 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 100:
#line 609 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP1(var("not",m((yylsp[-1]))), TAPP2(var("==",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))), m((yylsp[-2]),(yylsp[0]))); }
#line 3267 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 101:
#line 610 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("<",m((yylsp[-1]))),  (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3273 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 102:
#line 611 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("<=",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3279 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 103:
#line 612 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var(">",m((yylsp[-1]))),  (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3285 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 104:
#line 613 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var(">=",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3291 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 105:
#line 614 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3297 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 106:
#line 616 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("+",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3303 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 107:
#line 617 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("-",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3309 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 108:
#line 618 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("append",m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]),(yylsp[0]))); }
#line 3315 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 109:
#line 619 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP1(var("neg",m((yylsp[-1]))), ExprPtr((yyvsp[0].exp)), m((yylsp[-1]),(yylsp[0]))); }
#line 3321 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 110:
#line 620 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3327 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 111:
#line 622 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("*", m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]), (yylsp[0]))); }
#line 3333 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 112:
#line 623 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("/", m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]), (yylsp[0]))); }
#line 3339 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 113:
#line 624 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = TAPP2(var("%", m((yylsp[-1]))), (yyvsp[-2].exp), (yyvsp[0].exp), m((yylsp[-2]), (yylsp[0]))); }
#line 3345 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 114:
#line 625 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3351 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 115:
#line 627 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = (yyvsp[0].exp); }
#line 3357 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 116:
#line 630 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileNestedLetMatch(*(yyvsp[-2].letbindings), ExprPtr((yyvsp[0].exp)), m((yylsp[-3]),(yylsp[0])))->clone(); }
#line 3363 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 117:
#line 631 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileNestedLetMatch(*(yyvsp[-3].letbindings), ExprPtr((yyvsp[0].exp)), m((yylsp[-4]),(yylsp[0])))->clone(); }
#line 3369 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 118:
#line 634 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileMatch(yyParseCC, *(yyvsp[-2].exps), normPatternRules(*(yyvsp[0].patternexps), m((yylsp[-3]),(yylsp[0]))), m((yylsp[-3]),(yylsp[0])))->clone(); }
#line 3375 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 119:
#line 637 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileMatchTest(yyParseCC, ExprPtr((yyvsp[-2].exp)), PatternPtr((yyvsp[0].pattern)), m((yylsp[-2]),(yylsp[0])))->clone(); }
#line 3381 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 120:
#line 640 "hexpr.y" /* yacc.c:1652  */
    {
        try {
          (yyval.exp) = makeParser(yyParseCC, *(yyvsp[-1].prules), m((yylsp[-3]),(yylsp[0])))->clone();
        } catch (hobbes::compile_table_failure& ctf) {
          std::ostringstream ss;
          ss << ctf.what() << std::endl;
          ctf.print(ss);
          throw annotated_error(m((yylsp[-3]),(yylsp[0])), ss.str());
        }
      }
#line 3396 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 121:
#line 652 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileNestedLetMatch(*(yyvsp[-1].letbindings), ExprPtr(new Unit(m((yylsp[-3]),(yylsp[0])))), m((yylsp[-3]),(yylsp[0]))); }
#line 3402 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 122:
#line 653 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileNestedLetMatch(*(yyvsp[-3].letbindings), ExprPtr((yyvsp[-1].exp)), m((yylsp[-5]),(yylsp[0]))); }
#line 3408 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 123:
#line 656 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Assump(ExprPtr((yyvsp[-2].exp)), QualTypePtr((yyvsp[0].qualtype)), m((yylsp[-2]),(yylsp[0]))); }
#line 3414 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 124:
#line 658 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-2].letbindings)->push_back(*(yyvsp[0].letbinding)); (yyval.letbindings) = (yyvsp[-2].letbindings); }
#line 3420 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 125:
#line 659 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbindings) = autorelease(new LetBindings()); (yyval.letbindings)->push_back(*(yyvsp[0].letbinding)); }
#line 3426 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 126:
#line 661 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbinding) = autorelease(new LetBinding(PatternPtr((yyvsp[-2].pattern)), ExprPtr((yyvsp[0].exp)))); }
#line 3432 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 127:
#line 663 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbindings) = (yyvsp[-1].letbindings); (yyval.letbindings)->push_back(*(yyvsp[0].letbinding)); }
#line 3438 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 128:
#line 664 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbindings) = autorelease(new LetBindings()); (yyval.letbindings)->push_back(*(yyvsp[0].letbinding)); }
#line 3444 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 129:
#line 666 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbinding) = autorelease(new LetBinding(PatternPtr((yyvsp[-3].pattern)), ExprPtr((yyvsp[-1].exp)))); }
#line 3450 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 130:
#line 667 "hexpr.y" /* yacc.c:1652  */
    { (yyval.letbinding) = autorelease(new LetBinding(PatternPtr(new MatchAny("_",m((yylsp[-1])))), ExprPtr((yyvsp[-1].exp)))); }
#line 3456 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 131:
#line 669 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = (yyvsp[-2].exps); (yyval.exps)->push_back(ExprPtr((yyvsp[0].exp))); }
#line 3462 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 132:
#line 670 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = autorelease(new Exprs()); (yyval.exps)->push_back(ExprPtr((yyvsp[0].exp))); }
#line 3468 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 133:
#line 672 "hexpr.y" /* yacc.c:1652  */
    { (yyval.cselection) = new CSelection(); (yyval.cselection)->pat = PatternPtr((yyvsp[-4].pattern)); (yyval.cselection)->seq = ExprPtr((yyvsp[-2].exp)); (yyval.cselection)->conds = *(yyvsp[0].exps); }
#line 3474 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 134:
#line 673 "hexpr.y" /* yacc.c:1652  */
    { (yyval.cselection) = new CSelection(); (yyval.cselection)->pat = PatternPtr((yyvsp[-2].pattern)); (yyval.cselection)->seq = ExprPtr((yyvsp[0].exp)); }
#line 3480 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 135:
#line 675 "hexpr.y" /* yacc.c:1652  */
    { (yyval.cselections) = (yyvsp[-2].cselections); (yyval.cselections)->push_back(CSelectionPtr((yyvsp[0].cselection))); }
#line 3486 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 136:
#line 676 "hexpr.y" /* yacc.c:1652  */
    { (yyval.cselections) = autorelease(new CSelections()); (yyval.cselections)->push_back(CSelectionPtr((yyvsp[0].cselection))); }
#line 3492 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 137:
#line 679 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new App(ExprPtr((yyvsp[-3].exp)), *(yyvsp[-1].exps), m((yylsp[-3]), (yylsp[0]))); }
#line 3498 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 138:
#line 680 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = varCtorFn(*(yyvsp[0].string), m((yylsp[0]))); }
#line 3504 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 139:
#line 683 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new App(var("range", m((yylsp[-2]))), list(ExprPtr((yyvsp[-3].exp)), ExprPtr((yyvsp[-1].exp))), m((yylsp[-4]), (yylsp[0]))); }
#line 3510 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 140:
#line 684 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new App(var("iterateS", m((yylsp[-1]))), list(ExprPtr((yyvsp[-2].exp)), fn(str::strings(".x"), fncall(var("+", m((yylsp[-1]))), list(var(".x", m((yylsp[-1]))), ExprPtr(new Int(1, m((yylsp[-1]))))), m((yylsp[-1]))), m((yylsp[-1])))), m((yylsp[-3]), (yylsp[0]))); }
#line 3516 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 141:
#line 685 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = desugarComprehension(yyParseCC, ExprPtr((yyvsp[-3].exp)), *(yyvsp[-1].cselections), m((yylsp[-4]), (yylsp[0]))); }
#line 3522 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 142:
#line 686 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new MkArray(*(yyvsp[-1].exps), m((yylsp[-2]), (yylsp[0]))); }
#line 3528 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 143:
#line 687 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new AIndex(ExprPtr((yyvsp[-3].exp)), ExprPtr((yyvsp[-1].exp)), m((yylsp[-3]), (yylsp[0]))); }
#line 3534 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 144:
#line 688 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new App(var("slice", m((yylsp[-2]))), list(ExprPtr((yyvsp[-5].exp)), ExprPtr((yyvsp[-3].exp)), ExprPtr((yyvsp[-1].exp))), m((yylsp[-5]), (yylsp[0]))); }
#line 3540 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 145:
#line 689 "hexpr.y" /* yacc.c:1652  */
    { std::string vn = freshName(); (yyval.exp) = new Let(vn, ExprPtr((yyvsp[-4].exp)), fncall(var("slice",m((yylsp[-1]))), list(var(vn,m((yylsp[-4]))), ExprPtr((yyvsp[-2].exp)), fncall(var("size",m((yylsp[-1]))), list(var(vn,m((yylsp[-4])))),m((yylsp[-4])))),m((yylsp[-4]),(yylsp[0]))), m((yylsp[-4]), (yylsp[0]))); }
#line 3546 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 146:
#line 690 "hexpr.y" /* yacc.c:1652  */
    { std::string vn = freshName(); (yyval.exp) = new Let(vn, ExprPtr((yyvsp[-4].exp)), fncall(var("slice",m((yylsp[-2]))), list(var(vn,m((yylsp[-4]))), fncall(var("size",m((yylsp[-2]))), list(var(vn,m((yylsp[-2])))),m((yylsp[-4]))), ExprPtr((yyvsp[-1].exp))), m((yylsp[-4]),(yylsp[0]))), m((yylsp[-4]), (yylsp[0]))); }
#line 3552 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 147:
#line 693 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new MkVariant(*(yyvsp[-3].string), ExprPtr((yyvsp[-1].exp)), m((yylsp[-4]), (yylsp[0]))); }
#line 3558 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 148:
#line 694 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new MkVariant(".f" + str::from((yyvsp[-3].intv)), ExprPtr((yyvsp[-1].exp)), m((yylsp[-4]), (yylsp[0]))); }
#line 3564 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 149:
#line 695 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new MkVariant(*(yyvsp[-1].string), ExprPtr(new Unit(m((yylsp[-1])))), m((yylsp[-2]), (yylsp[0]))); }
#line 3570 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 150:
#line 696 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Case(ExprPtr((yyvsp[-4].exp)), *(yyvsp[-1].vfields), m((yylsp[-5]), (yylsp[0]))); }
#line 3576 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 151:
#line 697 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Case(ExprPtr((yyvsp[-6].exp)), *(yyvsp[-3].vfields), ExprPtr((yyvsp[0].exp)), m((yylsp[-7]), (yylsp[0]))); }
#line 3582 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 152:
#line 700 "hexpr.y" /* yacc.c:1652  */
    { if ((yyvsp[-1].rfields)->size() > 0) { (yyval.exp) = new MkRecord(*(yyvsp[-1].rfields), m((yylsp[-2]), (yylsp[0]))); } else { (yyval.exp) = new Unit(m((yylsp[-2]), (yylsp[0]))); } }
#line 3588 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 153:
#line 701 "hexpr.y" /* yacc.c:1652  */
    { if ((yyvsp[-2].rfields)->size() > 0) { (yyval.exp) = new MkRecord(*(yyvsp[-2].rfields), m((yylsp[-3]), (yylsp[0]))); } else { (yyval.exp) = new Unit(m((yylsp[-3]), (yylsp[0]))); } }
#line 3594 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 154:
#line 702 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = makeProjSeq((yyvsp[-1].exp), *(yyvsp[0].strings), m((yylsp[-1]), (yylsp[0]))); }
#line 3600 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 155:
#line 705 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Fn(str::strings("x"), proj(var("x", m((yylsp[0]))), *(yyvsp[0].strings), m((yylsp[0]))), m((yylsp[0]))); }
#line 3606 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 156:
#line 708 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = compileRegexFn(yyParseCC, std::string((yyvsp[0].string)->begin() + 1, (yyvsp[0].string)->end() - 1), m((yylsp[0])))->clone(); }
#line 3612 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 157:
#line 711 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Pack(ExprPtr((yyvsp[0].exp)), m((yylsp[-1]), (yylsp[0]))); }
#line 3618 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 158:
#line 712 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Unpack(*(yyvsp[-4].string), ExprPtr((yyvsp[-2].exp)), ExprPtr((yyvsp[0].exp)), m((yylsp[-5]), (yylsp[0]))); }
#line 3624 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 159:
#line 715 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Bool((yyvsp[0].boolv), m((yylsp[0]))); }
#line 3630 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 160:
#line 716 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Char(str::readCharDef(*(yyvsp[0].string)), m((yylsp[0]))); }
#line 3636 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 161:
#line 717 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Byte(str::dehex(*(yyvsp[0].string)), m((yylsp[0]))); }
#line 3642 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 162:
#line 718 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = mkarray(str::dehexs(*(yyvsp[0].string)), m((yylsp[0]))); }
#line 3648 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 163:
#line 719 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Short((yyvsp[0].shortv), m((yylsp[0]))); }
#line 3654 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 164:
#line 720 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Int((yyvsp[0].intv), m((yylsp[0]))); }
#line 3660 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 165:
#line 721 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Long((yyvsp[0].longv), m((yylsp[0]))); }
#line 3666 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 166:
#line 722 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Int128((yyvsp[0].int128v), m((yylsp[0]))); }
#line 3672 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 167:
#line 723 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Float((yyvsp[0].floatv), m((yylsp[0]))); }
#line 3678 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 168:
#line 724 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Double((yyvsp[0].doublev), m((yylsp[0]))); }
#line 3684 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 169:
#line 725 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = mkarray(str::unescape(str::trimq(*(yyvsp[0].string))), m((yylsp[0]))); }
#line 3690 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 170:
#line 726 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = mkTimespanExpr(*(yyvsp[0].strings), m((yylsp[0])))->clone(); }
#line 3696 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 171:
#line 727 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = mkTimeExpr(*(yyvsp[0].string), m((yylsp[0])))->clone(); }
#line 3702 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 172:
#line 728 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = mkDateTimeExpr(*(yyvsp[0].string), m((yylsp[0])))->clone(); }
#line 3708 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 173:
#line 731 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = pickNestedExp((yyvsp[-1].exps), m((yylsp[-2]),(yylsp[0]))); }
#line 3714 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 174:
#line 734 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("append", m((yylsp[-1]))); }
#line 3720 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 175:
#line 735 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("+",      m((yylsp[-1]))); }
#line 3726 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 176:
#line 736 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("-",      m((yylsp[-1]))); }
#line 3732 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 177:
#line 737 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("*",      m((yylsp[-1]))); }
#line 3738 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 178:
#line 738 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("/",      m((yylsp[-1]))); }
#line 3744 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 179:
#line 739 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("%",      m((yylsp[-1]))); }
#line 3750 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 180:
#line 740 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("~",      m((yylsp[-1]))); }
#line 3756 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 181:
#line 741 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("===",    m((yylsp[-1]))); }
#line 3762 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 182:
#line 742 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("==",     m((yylsp[-1]))); }
#line 3768 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 183:
#line 743 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("!=",     m((yylsp[-1]))); }
#line 3774 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 184:
#line 744 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("<",      m((yylsp[-1]))); }
#line 3780 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 185:
#line 745 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var(">",      m((yylsp[-1]))); }
#line 3786 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 186:
#line 746 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var(">=",     m((yylsp[-1]))); }
#line 3792 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 187:
#line 747 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("<=",     m((yylsp[-1]))); }
#line 3798 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 188:
#line 748 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("and",    m((yylsp[-1]))); }
#line 3804 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 189:
#line 749 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("or",     m((yylsp[-1]))); }
#line 3810 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 190:
#line 750 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("in",     m((yylsp[-1]))); }
#line 3816 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 191:
#line 751 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Var("not",    m((yylsp[-1]))); }
#line 3822 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 192:
#line 754 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exp) = new Assump(fncall(var("unsafeCast", m((yylsp[-1]))), list(mktunit(m((yylsp[-1])))), m((yylsp[-1]))), qualtype(tapp(primty("quote"), list(texpr(ExprPtr((yyvsp[-1].exp)))))), m((yylsp[-1]))); }
#line 3828 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 193:
#line 756 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prules) = (yyvsp[-1].prules); (yyval.prules)->push_back(*(yyvsp[0].prule)); }
#line 3834 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 194:
#line 757 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prules) = autorelease(new Grammar()); (yyval.prules)->push_back(*(yyvsp[0].prule)); }
#line 3840 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 195:
#line 759 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prule) = autorelease(new Grammar::value_type(*(yyvsp[-2].string), *(yyvsp[0].prdefs))); }
#line 3846 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 196:
#line 761 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prdefs) = (yyvsp[-2].prdefs); (yyval.prdefs)->push_back(*(yyvsp[0].prdef)); }
#line 3852 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 197:
#line 762 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prdefs) = autorelease(new GrammarRules()); (yyval.prdefs)->push_back(*(yyvsp[0].prdef)); }
#line 3858 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 198:
#line 764 "hexpr.y" /* yacc.c:1652  */
    { (yyval.prdef) = autorelease(new GrammarRule(*(yyvsp[-3].pbelems), ExprPtr((yyvsp[-1].exp)))); }
#line 3864 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 199:
#line 766 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pbelems) = (yyvsp[-1].pbelems); (yyval.pbelems)->push_back(*(yyvsp[0].pbelem)); }
#line 3870 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 200:
#line 767 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pbelems) = autorelease(new BoundGrammarValues()); }
#line 3876 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 201:
#line 769 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pbelem) = autorelease(new BoundGrammarValue(*(yyvsp[-2].string), GrammarValuePtr((yyvsp[0].pvalue)))); }
#line 3882 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 202:
#line 770 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pbelem) = autorelease(new BoundGrammarValue("_", GrammarValuePtr((yyvsp[0].pvalue)))); }
#line 3888 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 203:
#line 772 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pvalue) = new GSymRef(*(yyvsp[0].string), m((yylsp[0]))); }
#line 3894 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 204:
#line 773 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pvalue) = new GStr(str::unescape(str::trimq(*(yyvsp[0].string))), m((yylsp[0]))); }
#line 3900 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 205:
#line 774 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pvalue) = new GStr(std::string(1, str::readCharDef(*(yyvsp[0].string))), m((yylsp[0]))); }
#line 3906 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 206:
#line 776 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3912 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 207:
#line 777 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[-1].strings); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 3918 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 208:
#line 779 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = (yyvsp[-1].exps); (yyval.exps)->push_back(ExprPtr((yyvsp[0].exp))); }
#line 3924 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 209:
#line 780 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = autorelease(new Exprs()); (yyval.exps)->push_back(ExprPtr((yyvsp[0].exp))); }
#line 3930 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 210:
#line 782 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patternexps) = (yyvsp[-1].patternexps); (yyval.patternexps)->push_back(*(yyvsp[0].patternexp)); }
#line 3936 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 211:
#line 783 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patternexps) = autorelease(new PatternRows()); (yyval.patternexps)->push_back(*(yyvsp[0].patternexp)); }
#line 3942 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 212:
#line 785 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patternexp) = autorelease(new PatternRow(*(yyvsp[-2].patterns), ExprPtr((yyvsp[0].exp)))); }
#line 3948 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 213:
#line 786 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patternexp) = autorelease(new PatternRow(*(yyvsp[-4].patterns), ExprPtr((yyvsp[-2].exp)), ExprPtr((yyvsp[0].exp)))); }
#line 3954 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 214:
#line 789 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = (yyvsp[-1].patterns); (yyval.patterns)->push_back(PatternPtr((yyvsp[0].pattern))); }
#line 3960 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 215:
#line 790 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = autorelease(new Patterns()); (yyval.patterns)->push_back(PatternPtr((yyvsp[0].pattern))); }
#line 3966 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 216:
#line 792 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Bool((yyvsp[0].boolv), m((yylsp[0])))), m((yylsp[0]))); }
#line 3972 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 217:
#line 793 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Char(str::readCharDef(*(yyvsp[0].string)), m((yylsp[0])))), m((yylsp[0]))); }
#line 3978 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 218:
#line 794 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Byte(str::dehex(*(yyvsp[0].string)), m((yylsp[0])))), m((yylsp[0]))); }
#line 3984 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 219:
#line 795 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Short((yyvsp[0].shortv), m((yylsp[0])))), m((yylsp[0]))); }
#line 3990 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 220:
#line 796 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Int((yyvsp[0].intv), m((yylsp[0])))), m((yylsp[0]))); }
#line 3996 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 221:
#line 797 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Long((yyvsp[0].longv), m((yylsp[0])))), m((yylsp[0]))); }
#line 4002 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 222:
#line 798 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Int128((yyvsp[0].int128v), m((yylsp[0])))), m((yylsp[0]))); }
#line 4008 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 223:
#line 799 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(PrimitivePtr(new Double((yyvsp[0].doublev), m((yylsp[0])))), m((yylsp[0]))); }
#line 4014 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 224:
#line 800 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = mkpatarray(str::dehexs(*(yyvsp[0].string)), m((yylsp[0]))); }
#line 4020 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 225:
#line 801 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = mkpatarray(str::unescape(str::trimq(*(yyvsp[0].string))), m((yylsp[0]))); }
#line 4026 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 226:
#line 802 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(mkTimespanPrim(*(yyvsp[0].strings), m((yylsp[0]))), mkTimespanExpr(*(yyvsp[0].strings), m((yylsp[0]))), m((yylsp[0]))); }
#line 4032 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 227:
#line 803 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(mkTimePrim(*(yyvsp[0].string), m((yylsp[0]))), mkTimeExpr(*(yyvsp[0].string), m((yylsp[0]))), m((yylsp[0]))); }
#line 4038 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 228:
#line 804 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchLiteral(mkDateTimePrim(*(yyvsp[0].string), m((yylsp[0]))), mkDateTimeExpr(*(yyvsp[0].string), m((yylsp[0]))), m((yylsp[0]))); }
#line 4044 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 229:
#line 805 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchRegex(std::string((yyvsp[0].string)->begin() + 1, (yyvsp[0].string)->end() - 1), m((yylsp[0]))); }
#line 4050 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 230:
#line 806 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchArray(*(yyvsp[-1].patterns), m((yylsp[-2]),(yylsp[0]))); }
#line 4056 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 231:
#line 807 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchArray(*(yyvsp[-2].patterns), m((yylsp[-3]),(yylsp[0]))); }
#line 4062 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 232:
#line 808 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchVariant(*(yyvsp[-1].string), PatternPtr(new MatchLiteral(PrimitivePtr(new Unit(m((yylsp[-1])))), m((yylsp[-1])))), m((yylsp[-2]),(yylsp[0]))); }
#line 4068 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 233:
#line 809 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchVariant(*(yyvsp[-3].string), PatternPtr((yyvsp[-1].pattern)), m((yylsp[-4]),(yylsp[0]))); }
#line 4074 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 234:
#line 810 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchVariant(".f" + str::from((yyvsp[-3].intv)), PatternPtr((yyvsp[-1].pattern)), m((yylsp[-4]),(yylsp[0]))); }
#line 4080 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 235:
#line 811 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = pickNestedPat((yyvsp[-1].patterns), m((yylsp[-2]),(yylsp[0]))); }
#line 4086 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 236:
#line 812 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = pickNestedPat((yyvsp[-2].patterns), m((yylsp[-3]),(yylsp[0]))); }
#line 4092 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 237:
#line 813 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchRecord(*(yyvsp[-1].recpatfields), m((yylsp[-2]),(yylsp[0]))); }
#line 4098 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 238:
#line 814 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchRecord(*(yyvsp[-2].recpatfields), m((yylsp[-3]),(yylsp[0]))); }
#line 4104 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 239:
#line 815 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = patVarCtorFn(*(yyvsp[0].string), m((yylsp[0]))); }
#line 4110 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 240:
#line 817 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchAny(*(yyvsp[0].string), m((yylsp[0]))); }
#line 4116 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 241:
#line 818 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = pickNestedPat((yyvsp[-1].patterns), m((yylsp[-2]),(yylsp[0]))); }
#line 4122 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 242:
#line 819 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = pickNestedPat((yyvsp[-2].patterns), m((yylsp[-3]),(yylsp[0]))); }
#line 4128 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 243:
#line 820 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchRecord(*(yyvsp[-1].recpatfields), m((yylsp[-2]),(yylsp[0]))); }
#line 4134 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 244:
#line 821 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = new MatchRecord(*(yyvsp[-2].recpatfields), m((yylsp[-3]),(yylsp[0]))); }
#line 4140 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 245:
#line 823 "hexpr.y" /* yacc.c:1652  */
    { (yyval.pattern) = (yyvsp[0].pattern); }
#line 4146 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 246:
#line 825 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = (yyvsp[0].patterns); }
#line 4152 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 247:
#line 826 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = new Patterns(); }
#line 4158 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 248:
#line 828 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = (yyvsp[-2].patterns); (yyval.patterns)->push_back(PatternPtr((yyvsp[0].pattern))); }
#line 4164 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 249:
#line 829 "hexpr.y" /* yacc.c:1652  */
    { (yyval.patterns) = new Patterns(); (yyval.patterns)->push_back(PatternPtr((yyvsp[0].pattern))); }
#line 4170 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 250:
#line 831 "hexpr.y" /* yacc.c:1652  */
    { (yyval.recpatfields) = (yyvsp[-2].recpatfields); (yyval.recpatfields)->push_back(*(yyvsp[0].recpatfield)); }
#line 4176 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 251:
#line 832 "hexpr.y" /* yacc.c:1652  */
    { (yyval.recpatfields) = new MatchRecord::Fields(); (yyval.recpatfields)->push_back(*(yyvsp[0].recpatfield)); }
#line 4182 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 252:
#line 834 "hexpr.y" /* yacc.c:1652  */
    { (yyval.recpatfield) = new MatchRecord::Field(*(yyvsp[-2].string), PatternPtr((yyvsp[0].pattern))); }
#line 4188 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 253:
#line 836 "hexpr.y" /* yacc.c:1652  */
    { (yyval.rfields) = autorelease(new MkRecord::FieldDefs()); }
#line 4194 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 254:
#line 837 "hexpr.y" /* yacc.c:1652  */
    { (yyval.rfields) = autorelease(new MkRecord::FieldDefs()); (yyval.rfields)->push_back(MkRecord::FieldDef(*(yyvsp[-2].string), ExprPtr((yyvsp[0].exp)))); }
#line 4200 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 255:
#line 838 "hexpr.y" /* yacc.c:1652  */
    { (yyval.rfields) = (yyvsp[-4].rfields);                                     (yyval.rfields)->push_back(MkRecord::FieldDef(*(yyvsp[-2].string), ExprPtr((yyvsp[0].exp)))); }
#line 4206 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 256:
#line 840 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4212 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 257:
#line 841 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("data")); }
#line 4218 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 258:
#line 842 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("type")); }
#line 4224 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 259:
#line 843 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("where")); }
#line 4230 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 260:
#line 844 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("class")); wantIndent(false); }
#line 4236 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 261:
#line 845 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("instance")); wantIndent(false); }
#line 4242 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 262:
#line 846 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("exists")); }
#line 4248 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 263:
#line 847 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("import")); }
#line 4254 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 264:
#line 848 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("module")); }
#line 4260 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 265:
#line 849 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("parse")); }
#line 4266 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 266:
#line 850 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("do")); }
#line 4272 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 267:
#line 851 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("return")); }
#line 4278 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 268:
#line 852 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string("fn")); }
#line 4284 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 269:
#line 853 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = autorelease(new std::string(".f" + str::from((yyvsp[0].intv)))); }
#line 4290 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 270:
#line 855 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[-2].strings); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 4296 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 271:
#line 856 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = (yyvsp[-1].strings); str::seq x = tupSectionFields(*(yyvsp[0].string)); (yyval.strings)->insert((yyval.strings)->end(), x.begin(), x.end()); }
#line 4302 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 272:
#line 857 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); (yyval.strings)->push_back(*(yyvsp[0].string)); }
#line 4308 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 273:
#line 858 "hexpr.y" /* yacc.c:1652  */
    { (yyval.strings) = autorelease(new str::seq()); *(yyval.strings) = tupSectionFields(*(yyvsp[0].string)); }
#line 4314 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 274:
#line 860 "hexpr.y" /* yacc.c:1652  */
    { (yyval.vfields) = autorelease(new Case::Bindings()); (yyval.vfields)->push_back(*(yyvsp[0].vbind)); }
#line 4320 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 275:
#line 861 "hexpr.y" /* yacc.c:1652  */
    { (yyval.vfields) = (yyvsp[-2].vfields); (yyval.vfields)->push_back(*(yyvsp[0].vbind)); }
#line 4326 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 276:
#line 863 "hexpr.y" /* yacc.c:1652  */
    { (yyval.vbind) = autorelease(new Case::Binding(*(yyvsp[-2].string), *(yyvsp[-2].string), ExprPtr((yyvsp[0].exp)))); }
#line 4332 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 277:
#line 864 "hexpr.y" /* yacc.c:1652  */
    { (yyval.vbind) = autorelease(new Case::Binding(*(yyvsp[-4].string), *(yyvsp[-2].string), ExprPtr((yyvsp[0].exp)))); }
#line 4338 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 278:
#line 865 "hexpr.y" /* yacc.c:1652  */
    { (yyval.vbind) = autorelease(new Case::Binding(".f" + str::from((yyvsp[-4].intv)), *(yyvsp[-2].string), ExprPtr((yyvsp[0].exp)))); }
#line 4344 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 279:
#line 867 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = autorelease(new Exprs()); }
#line 4350 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 280:
#line 868 "hexpr.y" /* yacc.c:1652  */
    { (yyval.exps) = autorelease(new Exprs()); (yyval.exps)->push_back(ExprPtr((yyvsp[0].exp))); }
#line 4356 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 281:
#line 869 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-2].exps)->push_back(ExprPtr((yyvsp[0].exp))); (yyval.exps) = (yyvsp[-2].exps); }
#line 4362 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 282:
#line 871 "hexpr.y" /* yacc.c:1652  */
    { (yyval.qualtype) = new QualType(*(yyvsp[-2].tconstraints), *(yyvsp[0].mtype)); }
#line 4368 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 283:
#line 872 "hexpr.y" /* yacc.c:1652  */
    { (yyval.qualtype) = new QualType(Constraints(), *(yyvsp[0].mtype)); }
#line 4374 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 284:
#line 875 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraints) = (yyvsp[-1].tconstraints); }
#line 4380 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 285:
#line 877 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraints) = autorelease(new Constraints()); (yyval.tconstraints)->push_back(ConstraintPtr((yyvsp[0].tconstraint))); }
#line 4386 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 286:
#line 878 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-2].tconstraints)->push_back(ConstraintPtr((yyvsp[0].tconstraint))); (yyval.tconstraints) = (yyvsp[-2].tconstraints); }
#line 4392 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 287:
#line 880 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(*(yyvsp[-1].string), *(yyvsp[0].mtypes)); }
#line 4398 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 288:
#line 881 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(EqualTypes::constraintName(), list(*(yyvsp[-2].mtype), *(yyvsp[0].mtype))); }
#line 4404 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 289:
#line 882 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(NotEqualTypes::constraintName(), list(*(yyvsp[-2].mtype), *(yyvsp[0].mtype))); }
#line 4410 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 290:
#line 883 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(FixIsoRecur::constraintName(), list(*(yyvsp[-2].mtype), *(yyvsp[0].mtype))); }
#line 4416 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 291:
#line 884 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(1), tlong(0), *(yyvsp[-6].mtype), freshTypeVar(),  *(yyvsp[-3].mtype), *(yyvsp[-1].mtype))); }
#line 4422 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 292:
#line 885 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(1), tlong(0), *(yyvsp[-8].mtype), TVar::make(*(yyvsp[-5].string)), *(yyvsp[-3].mtype), *(yyvsp[-1].mtype))); }
#line 4428 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 293:
#line 886 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(1), tlong(1), *(yyvsp[-6].mtype), freshTypeVar(),  *(yyvsp[-3].mtype), *(yyvsp[-1].mtype))); }
#line 4434 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 294:
#line 887 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(0), tlong(0), *(yyvsp[0].mtype), freshTypeVar(),  *(yyvsp[-5].mtype), *(yyvsp[-3].mtype))); }
#line 4440 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 295:
#line 888 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(0), tlong(0), *(yyvsp[0].mtype), TVar::make(*(yyvsp[-7].string)), *(yyvsp[-5].mtype), *(yyvsp[-3].mtype))); }
#line 4446 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 296:
#line 889 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(RecordDeconstructor::constraintName(), list(tlong(0), tlong(1), *(yyvsp[0].mtype), freshTypeVar(),  *(yyvsp[-5].mtype), *(yyvsp[-3].mtype))); }
#line 4452 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 297:
#line 891 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = HasField::newConstraint(HasField::Read,  *(yyvsp[-4].mtype), TString::make(*(yyvsp[-2].string)), *(yyvsp[0].mtype)); }
#line 4458 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 298:
#line 892 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = HasField::newConstraint(HasField::Write, *(yyvsp[-4].mtype), TString::make(*(yyvsp[-2].string)), *(yyvsp[0].mtype)); }
#line 4464 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 299:
#line 893 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = HasField::newConstraint(HasField::Read,  *(yyvsp[-4].mtype), *(yyvsp[-2].mtype),                *(yyvsp[0].mtype)); }
#line 4470 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 300:
#line 894 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = HasField::newConstraint(HasField::Write, *(yyvsp[-4].mtype), *(yyvsp[-2].mtype),                *(yyvsp[0].mtype)); }
#line 4476 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 301:
#line 896 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(VariantDeconstructor::constraintName(), list(tlong(1), *(yyvsp[-6].mtype), freshTypeVar(),  *(yyvsp[-3].mtype), *(yyvsp[-1].mtype))); }
#line 4482 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 302:
#line 897 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(VariantDeconstructor::constraintName(), list(tlong(0), *(yyvsp[0].mtype), freshTypeVar(),  *(yyvsp[-5].mtype), *(yyvsp[-3].mtype))); }
#line 4488 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 303:
#line 898 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(VariantDeconstructor::constraintName(), list(tlong(1), *(yyvsp[-8].mtype), TVar::make(*(yyvsp[-5].string)), *(yyvsp[-3].mtype), *(yyvsp[-1].mtype))); }
#line 4494 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 304:
#line 899 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(VariantDeconstructor::constraintName(), list(tlong(0), *(yyvsp[0].mtype), TVar::make(*(yyvsp[-7].string)), *(yyvsp[-5].mtype), *(yyvsp[-3].mtype))); }
#line 4500 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 305:
#line 901 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(CtorVerifier::constraintName(), list(*(yyvsp[0].mtype), TString::make(*(yyvsp[-5].string)), *(yyvsp[-3].mtype))); }
#line 4506 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 306:
#line 902 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(CtorVerifier::constraintName(), list(*(yyvsp[0].mtype), *(yyvsp[-5].mtype),                *(yyvsp[-3].mtype))); }
#line 4512 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 307:
#line 903 "hexpr.y" /* yacc.c:1652  */
    { (yyval.tconstraint) = new Constraint(AppendsToUnqualifier::constraintName(), list(*(yyvsp[-4].mtype), *(yyvsp[-2].mtype), *(yyvsp[0].mtype))); }
#line 4518 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 308:
#line 905 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4524 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 309:
#line 906 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-1].mtypes)->push_back(*(yyvsp[0].mtype)); (yyval.mtypes) = (yyvsp[-1].mtypes); }
#line 4530 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 310:
#line 908 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = (yyvsp[-1].mtypes); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4536 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 311:
#line 909 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4542 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 312:
#line 911 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Func::make(tuplety(*(yyvsp[-2].mtypes)), *(yyvsp[0].mtype)))); }
#line 4548 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 313:
#line 912 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(makeTupleType(*(yyvsp[0].mtypes)))); }
#line 4554 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 314:
#line 913 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(makeSumType(*(yyvsp[0].mtypes)))); }
#line 4560 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 315:
#line 915 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(monoTypeByName(*(yyvsp[0].string)))); }
#line 4566 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 316:
#line 916 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(OpaquePtr::make(str::replace<char>(*(yyvsp[-1].string), ".", "::"), 0, false))); }
#line 4572 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 317:
#line 917 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Prim::make("[]"))); }
#line 4578 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 318:
#line 918 "hexpr.y" /* yacc.c:1652  */
    { try { (yyval.mtype) = autorelease(new MonoTypePtr(Array::make(yyParseCC->replaceTypeAliases(accumTApp(*(yyvsp[-1].mtypes)))))); } catch (std::exception& ex) { throw annotated_error(m((yylsp[-1])), ex.what()); } }
#line 4584 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 319:
#line 919 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(FixedArray::make(*(yyvsp[-4].mtype), *(yyvsp[-2].mtype)))); }
#line 4590 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 320:
#line 920 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Prim::make("->"))); }
#line 4596 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 321:
#line 921 "hexpr.y" /* yacc.c:1652  */
    { try { (yyval.mtype) = autorelease(new MonoTypePtr(clone(yyParseCC->replaceTypeAliases(accumTApp(*(yyvsp[-1].mtypes)))))); } catch (std::exception& ex) { throw annotated_error(m((yylsp[-1])), ex.what()); } }
#line 4602 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 322:
#line 922 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(makeRecType(*(yyvsp[-1].mreclist)))); }
#line 4608 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 323:
#line 923 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(makeVarType(*(yyvsp[-1].mvarlist)))); }
#line 4614 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 324:
#line 924 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Prim::make("unit"))); }
#line 4620 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 325:
#line 925 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(((yyvsp[0].intv) == 0) ? Prim::make("void") : TLong::make((yyvsp[0].intv)))); }
#line 4626 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 326:
#line 926 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr((yyvsp[0].boolv) ? TLong::make(1) : TLong::make(0))); }
#line 4632 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 327:
#line 927 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Exists::make(*(yyvsp[-2].string), *(yyvsp[0].mtype)))); }
#line 4638 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 328:
#line 928 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(fileRefTy(*(yyvsp[-2].mtype), *(yyvsp[0].mtype)))); }
#line 4644 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 329:
#line 929 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(fileRefTy(*(yyvsp[-2].mtype)))); }
#line 4650 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 330:
#line 930 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(Recursive::make(*(yyvsp[-2].string), *(yyvsp[0].mtype)))); }
#line 4656 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 331:
#line 931 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(TString::make(str::unescape(str::trimq(*(yyvsp[0].string)))))); }
#line 4662 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 332:
#line 932 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(TApp::make(primty("quote"), list(texpr(ExprPtr((yyvsp[-1].exp))))))); }
#line 4668 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 333:
#line 934 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(TVar::make(*(yyvsp[0].string)))); }
#line 4674 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 334:
#line 935 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtype) = autorelease(new MonoTypePtr(TLong::make((yyvsp[0].intv)))); }
#line 4680 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 335:
#line 937 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[0].string); }
#line 4686 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 336:
#line 938 "hexpr.y" /* yacc.c:1652  */
    { (yyval.string) = (yyvsp[-2].string); *(yyval.string) += "."; *(yyval.string) += *(yyvsp[0].string); }
#line 4692 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 337:
#line 940 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4698 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 338:
#line 941 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-1].mtypes)->insert((yyvsp[-1].mtypes)->begin(), *(yyvsp[-3].mtype)); (yyval.mtypes) = (yyvsp[-1].mtypes); }
#line 4704 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 339:
#line 943 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4710 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 340:
#line 944 "hexpr.y" /* yacc.c:1652  */
    { (yyvsp[-2].mtypes)->push_back(*(yyvsp[0].mtype)); (yyval.mtypes) = (yyvsp[-2].mtypes); }
#line 4716 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 341:
#line 946 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4722 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 342:
#line 947 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = (yyvsp[-2].mtypes); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4728 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 343:
#line 949 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = autorelease(new MonoTypes()); (yyval.mtypes)->push_back(*(yyvsp[-2].mtype)); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4734 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 344:
#line 950 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mtypes) = (yyvsp[-2].mtypes); (yyval.mtypes)->push_back(*(yyvsp[0].mtype)); }
#line 4740 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 345:
#line 952 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mreclist) = (yyvsp[-4].mreclist);                                 (yyval.mreclist)->push_back(Record::Member(*(yyvsp[-2].string), *(yyvsp[0].mtype))); }
#line 4746 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 346:
#line 953 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mreclist) = autorelease(new Record::Members()); (yyval.mreclist)->push_back(Record::Member(*(yyvsp[-2].string), *(yyvsp[0].mtype))); }
#line 4752 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 347:
#line 955 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvarlist) = (yyvsp[-4].mvarlist);                                  (yyval.mvarlist)->push_back(Variant::Member(*(yyvsp[-2].string), *(yyvsp[0].mtype),                0)); }
#line 4758 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 348:
#line 956 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvarlist) = (yyvsp[-2].mvarlist);                                  (yyval.mvarlist)->push_back(Variant::Member(*(yyvsp[0].string), Prim::make("unit"), 0)); }
#line 4764 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 349:
#line 957 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvarlist) = autorelease(new Variant::Members()); (yyval.mvarlist)->push_back(Variant::Member(*(yyvsp[-2].string), *(yyvsp[0].mtype),                0)); }
#line 4770 "hexpr.parse.C" /* yacc.c:1652  */
    break;

  case 350:
#line 958 "hexpr.y" /* yacc.c:1652  */
    { (yyval.mvarlist) = autorelease(new Variant::Members()); (yyval.mvarlist)->push_back(Variant::Member(*(yyvsp[0].string), Prim::make("unit"), 0)); }
#line 4776 "hexpr.parse.C" /* yacc.c:1652  */
    break;


#line 4780 "hexpr.parse.C" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 962 "hexpr.y" /* yacc.c:1918  */

#pragma GCC diagnostic pop

