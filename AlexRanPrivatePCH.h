#pragma once
#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAlexRan, Log, All);

#define ALEXRAN_LOG_HELPER(VERBOSITY, LOG_TEXT, ...) \
    do \
    { \
        UE_LOG( LogAlexRan, VERBOSITY, LOG_TEXT, ##__VA_ARGS__ ); \
    } \
    while ( 0 )

#define ALEXRAN_LOG_MESSAGE( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Log, LogAlexRan, ##__VA_ARGS__ )

#define ALEXRAN_LOG_FATAL( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Fatal, LogAlexRan, ##__VA_ARGS__ )

#define ALEXRAN_LOG_ERROR( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Error, LogAlexRan, ##__VA_ARGS__ )

#define ALEXRAN_LOG_WARNING( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Warning, LogAlexRan, ##__VA_ARGS__ )

#define ALEXRAN_LOG_DISPLAY( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Display, LogAlexRan, ##__VA_ARGS__ )

#define ALEXRAN_LOG_VERBOSE( LogAlexRan, ... ) \
    ALEXRAN_LOG_HELPER( Verbose, LogAlexRan, ##__VA_ARGS__ )

#ifndef _DEBUG

#define ALEXRAN_CHECK_CONDITION(CONDITION)\
	do if (!(CONDITION))\
	{\
		ALEXRAN_LOG_ERROR(TEXT("%s [%s] must be invalid."), __FUNCTIONW__, TEXT(#CONDITION));\
	} while(0)

#else

#define ALEXRAN_CHECK_CONDITION(CONDITION)\
	do if (!(CONDITION))\
	{\
		ALEXRAN_LOG_FATAL(TEXT("%s [%s] must be invalid."), __FUNCTIONW__, TEXT(#CONDITION));\
	} while(0)

#endif

#define ALEXRAN_DEBUG

#ifndef ALEXRAN_DEBUG

#define ALEXRAN_DEBUG(STR_VALUE) \
	do\
	{\
		ALEXRAN_LOG_DISPLAY(TEXT("%s called [%s]."), __FUNCTIONW__, STR_VALUE);\
	} while(0)

#else

#define ALEXRAN_DEBUG(STR_VALUE) \
	do\
	{\
	} while(0)

#endif

#ifdef Synchronizer_DEBUG

#define ALEXRAN_SYNCHRONIZER_DEBUG(STR_VALUE) \
	do\
	{\
		ALEXRAN_LOG_DISPLAY(TEXT("%s called [%s]."), __FUNCTIONW__, STR_VALUE);\
	} while(0)

#else

#define ALEXRAN_SYNCHRONIZER_DEBUG(STR_VALUE) \
	do\
	{\
	} while(0)

#endif

#define ALEXRAN_CHECK_CONDITION_RETURN(CONDITION, ...) \
	ALEXRAN_CHECK_CONDITION_RETURN_HELPER_X\
		(CONDITION, ##__VA_ARGS__ , _RESULT , _VOID)\
		(CONDITION, __VA_ARGS__)

#define ALEXRAN_CHECK_CONDITION_RETURN_HELPER_X(A, B, X, ...) \
	ALEXRAN_CHECK_CONDITION_RETURN_HELPER ## X

#define ALEXRAN_CHECK_CONDITION_RETURN_HELPER_VOID(CONDITION) \
	do if (!(CONDITION))\
	{\
		ALEXRAN_LOG_ERROR(TEXT("%s [%s] must be invalid."), __FUNCTIONW__, TEXT(#CONDITION));\
		return;\
	} while(0)

#define ALEXRAN_CHECK_CONDITION_RETURN_HELPER_RESULT(CONDITION,RETURN_VALUE) \
	do if (!(CONDITION))\
	{\
		ALEXRAN_LOG_ERROR(TEXT("%s [%s] must be invalid."), __FUNCTIONW__, TEXT(#CONDITION));\
		return RETURN_VALUE;\
	} while(0)

#define ALEXRAN_SAFE_RETURN_FROM_ARRAY(MY_ARRAY,INDEX,DEFAULT_VALUE) \
	do\
	{\
		if (INDEX >= 0 && INDEX < MY_ARRAY.Num()) return MY_ARRAY[INDEX];\
		ALEXRAN_LOG_ERROR(TEXT("%s try access array %s with out of bounds index : %i from an array of size %i"), __FUNCTIONW__, TEXT(#MY_ARRAY), INDEX,  MY_ARRAY.Num());\
		return DEFAULT_VALUE;\
	} while (0)