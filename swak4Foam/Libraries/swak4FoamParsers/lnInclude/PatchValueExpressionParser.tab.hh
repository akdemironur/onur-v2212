// A Bison parser, made by GNU Bison 3.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file PatchValueExpressionParser.tab.hh
 ** Define the parserPatch::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_PARSERPATCH_PATCHVALUEEXPRESSIONPARSER_TAB_HH_INCLUDED
# define YY_PARSERPATCH_PATCHVALUEEXPRESSIONPARSER_TAB_HH_INCLUDED


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "PatchValueExpressionParser_location.hh"


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

/* Debug traces.  */
#ifndef PARSERPATCHDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSERPATCHDEBUG 1
#  else
#   define PARSERPATCHDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSERPATCHDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSERPATCHDEBUG */

namespace parserPatch {
#line 164 "PatchValueExpressionParser.tab.hh"




  /// A Bison parser.
  class PatchValueExpressionParser
  {
  public:
#ifndef PARSERPATCHSTYPE
    /// Symbol semantic values.
    union semantic_type
    {
#line 82 "../PatchValueExpressionParser.yy"

    Foam::scalar val;
    Foam::label integer;
    Foam::vector *vec;
    Foam::word *name;
    Foam::vectorField *vfield;
    Foam::scalarField *sfield;
    Foam::Field<bool> *lfield;
    Foam::tensorField *tfield;
    Foam::symmTensorField *yfield;
    Foam::sphericalTensorField *hfield;

#line 190 "PatchValueExpressionParser.tab.hh"

    };
#else
    typedef PARSERPATCHSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_LINE = 258,
        TOKEN_LOOKUP = 259,
        TOKEN_LOOKUP2D = 260,
        TOKEN_SID = 261,
        TOKEN_VID = 262,
        TOKEN_LID = 263,
        TOKEN_TID = 264,
        TOKEN_YID = 265,
        TOKEN_HID = 266,
        TOKEN_PSID = 267,
        TOKEN_PVID = 268,
        TOKEN_PLID = 269,
        TOKEN_PTID = 270,
        TOKEN_PYID = 271,
        TOKEN_PHID = 272,
        TOKEN_FUNCTION_SID = 273,
        TOKEN_FUNCTION_PSID = 274,
        TOKEN_FUNCTION_VID = 275,
        TOKEN_FUNCTION_PVID = 276,
        TOKEN_FUNCTION_TID = 277,
        TOKEN_FUNCTION_PTID = 278,
        TOKEN_FUNCTION_YID = 279,
        TOKEN_FUNCTION_PYID = 280,
        TOKEN_FUNCTION_HID = 281,
        TOKEN_FUNCTION_PHID = 282,
        TOKEN_FUNCTION_LID = 283,
        TOKEN_FUNCTION_PLID = 284,
        TOKEN_NUM = 285,
        TOKEN_INT = 286,
        TOKEN_VEC = 287,
        START_DEFAULT = 301,
        START_FACE_SCALAR_COMMA = 302,
        START_FACE_SCALAR_CLOSE = 303,
        START_FACE_VECTOR_COMMA = 304,
        START_FACE_VECTOR_CLOSE = 305,
        START_FACE_TENSOR_COMMA = 306,
        START_FACE_TENSOR_CLOSE = 307,
        START_FACE_YTENSOR_COMMA = 308,
        START_FACE_YTENSOR_CLOSE = 309,
        START_FACE_HTENSOR_COMMA = 310,
        START_FACE_HTENSOR_CLOSE = 311,
        START_FACE_LOGICAL_COMMA = 312,
        START_FACE_LOGICAL_CLOSE = 313,
        START_POINT_SCALAR_COMMA = 314,
        START_POINT_SCALAR_CLOSE = 315,
        START_POINT_VECTOR_COMMA = 316,
        START_POINT_VECTOR_CLOSE = 317,
        START_POINT_TENSOR_COMMA = 318,
        START_POINT_TENSOR_CLOSE = 319,
        START_POINT_YTENSOR_COMMA = 320,
        START_POINT_YTENSOR_CLOSE = 321,
        START_POINT_HTENSOR_COMMA = 322,
        START_POINT_HTENSOR_CLOSE = 323,
        START_POINT_LOGICAL_COMMA = 324,
        START_POINT_LOGICAL_CLOSE = 325,
        START_CLOSE_ONLY = 326,
        START_COMMA_ONLY = 327,
        TOKEN_LAST_FUNCTION_CHAR = 328,
        TOKEN_IN_FUNCTION_CHAR = 329,
        TOKEN_VECTOR = 330,
        TOKEN_TENSOR = 331,
        TOKEN_SYMM_TENSOR = 332,
        TOKEN_SPHERICAL_TENSOR = 333,
        TOKEN_TRUE = 334,
        TOKEN_FALSE = 335,
        TOKEN_x = 336,
        TOKEN_y = 337,
        TOKEN_z = 338,
        TOKEN_xx = 339,
        TOKEN_xy = 340,
        TOKEN_xz = 341,
        TOKEN_yx = 342,
        TOKEN_yy = 343,
        TOKEN_yz = 344,
        TOKEN_zx = 345,
        TOKEN_zy = 346,
        TOKEN_zz = 347,
        TOKEN_ii = 348,
        TOKEN_unitTensor = 349,
        TOKEN_pi = 350,
        TOKEN_rand = 351,
        TOKEN_randFixed = 352,
        TOKEN_id = 353,
        TOKEN_dist = 354,
        TOKEN_randNormal = 355,
        TOKEN_randNormalFixed = 356,
        TOKEN_position = 357,
        TOKEN_area = 358,
        TOKEN_Sf = 359,
        TOKEN_Cn = 360,
        TOKEN_delta = 361,
        TOKEN_weights = 362,
        TOKEN_normal = 363,
        TOKEN_snGrad = 364,
        TOKEN_internalField = 365,
        TOKEN_neighbourField = 366,
        TOKEN_neighbourPatch = 367,
        TOKEN_oldTime = 368,
        TOKEN_deltaT = 369,
        TOKEN_time = 370,
        TOKEN_outputTime = 371,
        TOKEN_pow = 372,
        TOKEN_log = 373,
        TOKEN_exp = 374,
        TOKEN_mag = 375,
        TOKEN_magSqr = 376,
        TOKEN_sin = 377,
        TOKEN_cos = 378,
        TOKEN_tan = 379,
        TOKEN_min = 380,
        TOKEN_max = 381,
        TOKEN_minPosition = 382,
        TOKEN_maxPosition = 383,
        TOKEN_average = 384,
        TOKEN_sum = 385,
        TOKEN_sqr = 386,
        TOKEN_sqrt = 387,
        TOKEN_log10 = 388,
        TOKEN_asin = 389,
        TOKEN_acos = 390,
        TOKEN_atan = 391,
        TOKEN_atan2 = 392,
        TOKEN_sinh = 393,
        TOKEN_cosh = 394,
        TOKEN_tanh = 395,
        TOKEN_asinh = 396,
        TOKEN_acosh = 397,
        TOKEN_atanh = 398,
        TOKEN_erf = 399,
        TOKEN_erfc = 400,
        TOKEN_lgamma = 401,
        TOKEN_besselJ0 = 402,
        TOKEN_besselJ1 = 403,
        TOKEN_besselY0 = 404,
        TOKEN_besselY1 = 405,
        TOKEN_sign = 406,
        TOKEN_pos = 407,
        TOKEN_neg = 408,
        TOKEN_toPoint = 409,
        TOKEN_toFace = 410,
        TOKEN_mapped = 411,
        TOKEN_mappedInternal = 412,
        TOKEN_points = 413,
        TOKEN_transpose = 414,
        TOKEN_diag = 415,
        TOKEN_tr = 416,
        TOKEN_dev = 417,
        TOKEN_symm = 418,
        TOKEN_skew = 419,
        TOKEN_det = 420,
        TOKEN_cof = 421,
        TOKEN_inv = 422,
        TOKEN_sph = 423,
        TOKEN_twoSymm = 424,
        TOKEN_dev2 = 425,
        TOKEN_eigenValues = 426,
        TOKEN_eigenVectors = 427,
        TOKEN_cpu = 428,
        TOKEN_weight = 429,
        TOKEN_OR = 430,
        TOKEN_AND = 431,
        TOKEN_EQ = 432,
        TOKEN_NEQ = 433,
        TOKEN_LEQ = 434,
        TOKEN_GEQ = 435,
        TOKEN_NEG = 436,
        TOKEN_NOT = 437,
        TOKEN_HODGE = 438
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t,
                    YY_MOVE_REF (location_type) l);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v,
                    YY_RVREF (location_type) l);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {};

    /// Build a parser object.
    PatchValueExpressionParser (void * scanner_yyarg, PatchValueExpressionDriver& driver_yyarg, int start_token_yyarg, int numberOfFunctionChars_yyarg);
    virtual ~PatchValueExpressionParser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if PARSERPATCHDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);



  private:
    /// This class is not copiable.
    PatchValueExpressionParser (const PatchValueExpressionParser&);
    PatchValueExpressionParser& operator= (const PatchValueExpressionParser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned short yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if PARSERPATCHDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (size_type i)
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (int i)
      {
        return operator[] (size_type (i));
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (size_type i) const
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (int i) const
      {
        return operator[] (size_type (i));
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 6495,     ///< Last index in yytable_.
      yynnts_ = 44,  ///< Number of nonterminal symbols.
      yyfinal_ = 331, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 200  ///< Number of tokens.
    };


    // User arguments.
    void * scanner;
    PatchValueExpressionDriver& driver;
    int start_token;
    int numberOfFunctionChars;
  };


} // parserPatch
#line 871 "PatchValueExpressionParser.tab.hh"





#endif // !YY_PARSERPATCH_PATCHVALUEEXPRESSIONPARSER_TAB_HH_INCLUDED
