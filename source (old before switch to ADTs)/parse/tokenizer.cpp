
#line 1 "source/parse/tokenizer.rl"
#import <deque>
#import "parse/tokenizer.hpp"

#define EMIT(t) \
  Token tok; \
  tok.type = t; \
  tok.payloadStart = ts; \
  tok.payloadEnd = te; \
  tok.location = ts - data; \
  tokens.push_back(tok);


#line 16 "source/parse/tokenizer.c"
static const char _Tokenizer_actions[] = {
	0, 1, 0, 1, 1, 1, 9, 1, 
	10, 1, 11, 1, 12, 1, 13, 1, 
	14, 1, 15, 1, 16, 1, 17, 1, 
	18, 1, 19, 1, 20, 1, 21, 1, 
	22, 1, 23, 1, 24, 1, 25, 1, 
	26, 1, 27, 1, 28, 1, 29, 1, 
	30, 1, 31, 1, 32, 1, 33, 1, 
	34, 1, 35, 1, 36, 1, 37, 1, 
	38, 1, 39, 1, 40, 1, 41, 2, 
	2, 3, 2, 2, 4, 2, 2, 5, 
	2, 2, 6, 2, 2, 7, 2, 2, 
	8
};

static const unsigned char _Tokenizer_key_offsets[] = {
	0, 0, 1, 2, 40, 43, 48, 49, 
	50, 53, 55, 56, 58, 59, 66, 73, 
	80, 88, 96, 104, 112, 121, 129, 137, 
	145, 153, 161, 169, 177
};

static const char _Tokenizer_trans_keys[] = {
	38, 124, 10, 13, 32, 33, 38, 40, 
	41, 42, 43, 44, 45, 46, 47, 58, 
	60, 61, 62, 63, 91, 93, 95, 102, 
	105, 109, 110, 116, 121, 123, 124, 125, 
	9, 12, 48, 57, 65, 90, 97, 122, 
	32, 9, 13, 10, 13, 32, 9, 12, 
	61, 42, 62, 48, 57, 48, 57, 61, 
	61, 62, 61, 95, 48, 57, 65, 90, 
	97, 122, 95, 48, 57, 65, 90, 97, 
	122, 95, 48, 57, 65, 90, 97, 122, 
	95, 97, 48, 57, 65, 90, 98, 122, 
	95, 108, 48, 57, 65, 90, 97, 122, 
	95, 115, 48, 57, 65, 90, 97, 122, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	95, 110, 115, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 100, 48, 57, 65, 90, 97, 
	122, 95, 111, 48, 57, 65, 90, 97, 
	122, 95, 114, 48, 57, 65, 90, 97, 
	122, 95, 117, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 101, 48, 57, 65, 90, 97, 
	122, 95, 115, 48, 57, 65, 90, 97, 
	122, 0
};

static const char _Tokenizer_single_lengths[] = {
	0, 1, 1, 30, 1, 3, 1, 1, 
	1, 0, 1, 2, 1, 1, 1, 1, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 2, 2, 2, 2
};

static const char _Tokenizer_range_lengths[] = {
	0, 0, 0, 4, 1, 1, 0, 0, 
	1, 1, 0, 0, 0, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3
};

static const unsigned char _Tokenizer_index_offsets[] = {
	0, 0, 2, 4, 39, 42, 47, 49, 
	51, 54, 56, 58, 61, 63, 68, 73, 
	78, 84, 90, 96, 102, 109, 115, 121, 
	127, 133, 139, 145, 151
};

static const char _Tokenizer_indicies[] = {
	0, 1, 2, 1, 4, 4, 3, 5, 
	6, 7, 8, 9, 10, 11, 12, 13, 
	14, 16, 17, 18, 19, 20, 22, 23, 
	24, 26, 27, 28, 29, 30, 31, 32, 
	33, 34, 3, 15, 21, 25, 1, 3, 
	3, 35, 4, 4, 3, 3, 36, 38, 
	37, 40, 39, 42, 15, 41, 15, 43, 
	45, 44, 47, 48, 46, 50, 49, 21, 
	21, 21, 21, 51, 24, 24, 24, 24, 
	52, 25, 25, 25, 25, 53, 25, 54, 
	25, 25, 25, 52, 25, 55, 25, 25, 
	25, 52, 25, 56, 25, 25, 25, 52, 
	25, 57, 25, 25, 25, 52, 25, 58, 
	59, 25, 25, 25, 52, 25, 60, 25, 
	25, 25, 52, 25, 61, 25, 25, 25, 
	52, 25, 57, 25, 25, 25, 52, 25, 
	62, 25, 25, 25, 52, 25, 63, 25, 
	25, 25, 52, 25, 64, 25, 25, 25, 
	52, 25, 65, 25, 25, 25, 52, 25, 
	64, 25, 25, 25, 52, 0
};

static const char _Tokenizer_trans_targs[] = {
	3, 0, 3, 4, 5, 6, 1, 3, 
	3, 7, 3, 3, 8, 3, 3, 9, 
	3, 10, 11, 12, 3, 13, 3, 3, 
	14, 15, 16, 20, 21, 23, 24, 27, 
	3, 2, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 17, 18, 
	19, 15, 15, 15, 22, 15, 25, 26, 
	15, 28
};

static const char _Tokenizer_trans_actions[] = {
	19, 0, 21, 0, 0, 0, 0, 23, 
	25, 0, 5, 35, 0, 37, 7, 0, 
	39, 0, 0, 0, 45, 0, 27, 29, 
	0, 86, 0, 0, 0, 0, 0, 0, 
	31, 0, 33, 67, 47, 59, 13, 51, 
	9, 49, 43, 61, 53, 15, 57, 11, 
	41, 55, 17, 65, 63, 69, 0, 0, 
	0, 83, 77, 74, 0, 71, 0, 0, 
	80, 0
};

static const char _Tokenizer_to_state_actions[] = {
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0
};

static const char _Tokenizer_from_state_actions[] = {
	0, 0, 0, 3, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0
};

static const unsigned char _Tokenizer_eof_trans[] = {
	0, 0, 0, 0, 36, 37, 38, 40, 
	42, 44, 45, 47, 50, 52, 53, 54, 
	53, 53, 53, 53, 53, 53, 53, 53, 
	53, 53, 53, 53, 53
};

static const int Tokenizer_start = 3;
static const int Tokenizer_first_final = 3;
static const int Tokenizer_error = 0;

static const int Tokenizer_en_main = 3;


#line 71 "source/parse/tokenizer.rl"


std::deque<Token> tokenize(const std::string& content) {
    
    std::deque<Token> tokens;
    
    //Get string data
    char* data = const_cast<char*>(&(content[0]));
    size_t len = content.size();
    
    //Start
    char* p = data;
    
    //End
    char* pe = p + len;
    char* eof = pe;
    
    //State
    int cs = 0, act = 0, have = 0, curline = 1;
    char *ts, *te = 0;
    int done = 0;
    
    //Run the machine
    
#line 187 "source/parse/tokenizer.c"
	{
	cs = Tokenizer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 95 "source/parse/tokenizer.rl"
    
#line 197 "source/parse/tokenizer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _Tokenizer_actions + _Tokenizer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 218 "source/parse/tokenizer.c"
		}
	}

	_keys = _Tokenizer_trans_keys + _Tokenizer_key_offsets[cs];
	_trans = _Tokenizer_index_offsets[cs];

	_klen = _Tokenizer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _Tokenizer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _Tokenizer_indicies[_trans];
_eof_trans:
	cs = _Tokenizer_trans_targs[_trans];

	if ( _Tokenizer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _Tokenizer_actions + _Tokenizer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 48 "source/parse/tokenizer.rl"
	{act = 25;}
	break;
	case 4:
#line 49 "source/parse/tokenizer.rl"
	{act = 26;}
	break;
	case 5:
#line 50 "source/parse/tokenizer.rl"
	{act = 27;}
	break;
	case 6:
#line 54 "source/parse/tokenizer.rl"
	{act = 29;}
	break;
	case 7:
#line 55 "source/parse/tokenizer.rl"
	{act = 30;}
	break;
	case 8:
#line 64 "source/parse/tokenizer.rl"
	{act = 35;}
	break;
	case 9:
#line 21 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(ADD); }}
	break;
	case 10:
#line 24 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(SLASH); }}
	break;
	case 11:
#line 25 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(STARSTAR); }}
	break;
	case 12:
#line 27 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(EQEQ); }}
	break;
	case 13:
#line 28 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(EXCLAIMEQ); }}
	break;
	case 14:
#line 31 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(LTEQ); }}
	break;
	case 15:
#line 32 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(GTEQ); }}
	break;
	case 16:
#line 34 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(ANDAND); }}
	break;
	case 17:
#line 35 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(BARBAR); }}
	break;
	case 18:
#line 37 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(LPAREN); }}
	break;
	case 19:
#line 38 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(RPAREN); }}
	break;
	case 20:
#line 39 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(LSQUARE); }}
	break;
	case 21:
#line 40 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(RSQUARE); }}
	break;
	case 22:
#line 41 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(LCURLY); }}
	break;
	case 23:
#line 42 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(RCURLY); }}
	break;
	case 24:
#line 44 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(COMMA); }}
	break;
	case 25:
#line 45 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(DOT); }}
	break;
	case 26:
#line 46 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(COLON); }}
	break;
	case 27:
#line 57 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(FATARROW); }}
	break;
	case 28:
#line 58 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(ARROW); }}
	break;
	case 29:
#line 59 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(QUESTIONMARK); }}
	break;
	case 30:
#line 19 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(NEWLINE); }}
	break;
	case 31:
#line 22 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(MINUS); }}
	break;
	case 32:
#line 23 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(STAR); }}
	break;
	case 33:
#line 29 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(LT); }}
	break;
	case 34:
#line 30 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(LT); }}
	break;
	case 35:
#line 43 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(EQ); }}
	break;
	case 36:
#line 52 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(EXCLAIM); }}
	break;
	case 37:
#line 61 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(NUMBER); }}
	break;
	case 38:
#line 64 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(IDENT); }}
	break;
	case 39:
#line 65 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(TITLEIDENT); }}
	break;
	case 40:
#line 68 "source/parse/tokenizer.rl"
	{te = p;p--;{ }}
	break;
	case 41:
#line 1 "NONE"
	{	switch( act ) {
	case 25:
	{{p = ((te))-1;} EMIT(MOD); }
	break;
	case 26:
	{{p = ((te))-1;} EMIT(IS); }
	break;
	case 27:
	{{p = ((te))-1;} EMIT(IN); }
	break;
	case 29:
	{{p = ((te))-1;} EMIT(YES); }
	break;
	case 30:
	{{p = ((te))-1;} EMIT(NO); }
	break;
	case 35:
	{{p = ((te))-1;} EMIT(IDENT); }
	break;
	}
	}
	break;
#line 464 "source/parse/tokenizer.c"
		}
	}

_again:
	_acts = _Tokenizer_actions + _Tokenizer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 477 "source/parse/tokenizer.c"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _Tokenizer_eof_trans[cs] > 0 ) {
		_trans = _Tokenizer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

#line 96 "source/parse/tokenizer.rl"
    
    //Return the output
    return tokens;
}
