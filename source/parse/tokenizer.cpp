
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
	38, 1, 39, 1, 40, 1, 41, 1, 
	42, 2, 2, 3, 2, 2, 4, 2, 
	2, 5, 2, 2, 6, 2, 2, 7, 
	2, 2, 8
};

static const unsigned char _Tokenizer_key_offsets[] = {
	0, 0, 1, 6, 10, 16, 17, 56, 
	59, 64, 65, 66, 67, 73, 74, 76, 
	77, 84, 91, 98, 106, 114, 122, 130, 
	139, 147, 155, 163, 171, 179, 187, 195
};

static const char _Tokenizer_trans_keys[] = {
	38, 77, 107, 120, 48, 57, 77, 107, 
	48, 57, 48, 57, 65, 70, 97, 102, 
	124, 10, 13, 32, 33, 38, 40, 41, 
	42, 43, 44, 45, 46, 47, 48, 58, 
	60, 61, 62, 63, 91, 93, 95, 102, 
	105, 109, 110, 116, 121, 123, 124, 125, 
	9, 12, 49, 57, 65, 90, 97, 122, 
	32, 9, 13, 10, 13, 32, 9, 12, 
	61, 42, 62, 48, 57, 65, 70, 97, 
	102, 61, 61, 62, 61, 95, 48, 57, 
	65, 90, 97, 122, 95, 48, 57, 65, 
	90, 97, 122, 95, 48, 57, 65, 90, 
	97, 122, 95, 97, 48, 57, 65, 90, 
	98, 122, 95, 108, 48, 57, 65, 90, 
	97, 122, 95, 115, 48, 57, 65, 90, 
	97, 122, 95, 101, 48, 57, 65, 90, 
	97, 122, 95, 110, 115, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 100, 48, 57, 65, 
	90, 97, 122, 95, 111, 48, 57, 65, 
	90, 97, 122, 95, 114, 48, 57, 65, 
	90, 97, 122, 95, 117, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 101, 48, 57, 65, 
	90, 97, 122, 95, 115, 48, 57, 65, 
	90, 97, 122, 0
};

static const char _Tokenizer_single_lengths[] = {
	0, 1, 3, 2, 0, 1, 31, 1, 
	3, 1, 1, 1, 0, 1, 2, 1, 
	1, 1, 1, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 2
};

static const char _Tokenizer_range_lengths[] = {
	0, 0, 1, 1, 3, 0, 4, 1, 
	1, 0, 0, 0, 3, 0, 0, 0, 
	3, 3, 3, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3, 3, 3, 3
};

static const unsigned char _Tokenizer_index_offsets[] = {
	0, 0, 2, 7, 11, 15, 17, 53, 
	56, 61, 63, 65, 67, 71, 73, 76, 
	78, 83, 88, 93, 99, 105, 111, 117, 
	124, 130, 136, 142, 148, 154, 160, 166
};

static const char _Tokenizer_indicies[] = {
	0, 1, 3, 3, 4, 2, 1, 3, 
	3, 2, 1, 5, 5, 5, 1, 6, 
	1, 8, 8, 7, 9, 10, 11, 12, 
	13, 14, 15, 16, 17, 18, 19, 20, 
	21, 22, 23, 24, 26, 27, 28, 30, 
	31, 32, 33, 34, 35, 36, 37, 38, 
	7, 2, 25, 29, 1, 7, 7, 39, 
	8, 8, 7, 7, 40, 42, 41, 44, 
	43, 46, 45, 5, 5, 5, 47, 49, 
	48, 51, 52, 50, 54, 53, 25, 25, 
	25, 25, 55, 28, 28, 28, 28, 56, 
	29, 29, 29, 29, 57, 29, 58, 29, 
	29, 29, 56, 29, 59, 29, 29, 29, 
	56, 29, 60, 29, 29, 29, 56, 29, 
	61, 29, 29, 29, 56, 29, 62, 63, 
	29, 29, 29, 56, 29, 64, 29, 29, 
	29, 56, 29, 65, 29, 29, 29, 56, 
	29, 61, 29, 29, 29, 56, 29, 66, 
	29, 29, 29, 56, 29, 67, 29, 29, 
	29, 56, 29, 68, 29, 29, 29, 56, 
	29, 69, 29, 29, 29, 56, 29, 68, 
	29, 29, 29, 56, 0
};

static const char _Tokenizer_trans_targs[] = {
	6, 0, 3, 6, 4, 12, 6, 7, 
	8, 9, 1, 6, 6, 10, 6, 6, 
	11, 6, 6, 2, 6, 13, 14, 15, 
	6, 16, 6, 6, 17, 18, 19, 23, 
	24, 26, 27, 30, 6, 5, 6, 6, 
	6, 6, 6, 6, 6, 6, 6, 6, 
	6, 6, 6, 6, 6, 6, 6, 6, 
	6, 6, 20, 21, 22, 18, 18, 18, 
	25, 18, 28, 29, 18, 31
};

static const char _Tokenizer_trans_actions[] = {
	19, 0, 0, 47, 0, 0, 21, 0, 
	0, 0, 0, 23, 25, 0, 5, 35, 
	0, 37, 7, 0, 39, 0, 0, 0, 
	45, 0, 27, 29, 0, 88, 0, 0, 
	0, 0, 0, 0, 31, 0, 33, 69, 
	49, 61, 13, 53, 9, 51, 43, 63, 
	55, 15, 59, 11, 41, 57, 17, 67, 
	65, 71, 0, 0, 0, 85, 79, 76, 
	0, 73, 0, 0, 82, 0
};

static const char _Tokenizer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0
};

static const char _Tokenizer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 3, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0
};

static const unsigned char _Tokenizer_eof_trans[] = {
	0, 0, 0, 0, 0, 0, 0, 40, 
	41, 42, 44, 46, 48, 49, 51, 54, 
	56, 57, 58, 57, 57, 57, 57, 57, 
	57, 57, 57, 57, 57, 57, 57, 57
};

static const int Tokenizer_start = 6;
static const int Tokenizer_first_final = 6;
static const int Tokenizer_error = 0;

static const int Tokenizer_en_main = 6;


#line 72 "source/parse/tokenizer.rl"


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
    
#line 191 "source/parse/tokenizer.c"
	{
	cs = Tokenizer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 96 "source/parse/tokenizer.rl"
    
#line 201 "source/parse/tokenizer.c"
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
#line 222 "source/parse/tokenizer.c"
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
#line 65 "source/parse/tokenizer.rl"
	{act = 36;}
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
#line 61 "source/parse/tokenizer.rl"
	{te = p+1;{ EMIT(NUMBER); }}
	break;
	case 31:
#line 19 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(NEWLINE); }}
	break;
	case 32:
#line 22 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(MINUS); }}
	break;
	case 33:
#line 23 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(STAR); }}
	break;
	case 34:
#line 29 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(LT); }}
	break;
	case 35:
#line 30 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(LT); }}
	break;
	case 36:
#line 43 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(EQ); }}
	break;
	case 37:
#line 52 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(EXCLAIM); }}
	break;
	case 38:
#line 62 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(HEXNUMBER); }}
	break;
	case 39:
#line 65 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(IDENT); }}
	break;
	case 40:
#line 66 "source/parse/tokenizer.rl"
	{te = p;p--;{ EMIT(TITLEIDENT); }}
	break;
	case 41:
#line 69 "source/parse/tokenizer.rl"
	{te = p;p--;{ }}
	break;
	case 42:
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
	case 36:
	{{p = ((te))-1;} EMIT(IDENT); }
	break;
	}
	}
	break;
#line 472 "source/parse/tokenizer.c"
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
#line 485 "source/parse/tokenizer.c"
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

#line 97 "source/parse/tokenizer.rl"
    
    //Return the output
    return tokens;
}
