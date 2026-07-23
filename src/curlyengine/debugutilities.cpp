#include "debugutilities.h"


static bool bIgnoreAsserts = false;


/**
 * Check to see if the user decided to ignore all asserts. If the user still wants
 * to check assert, the expression is evaluated by forwarding info to AssertDetailed. 
 * The function will break at the defined assert line if this function is used in 
 * conjunction with a macro. 
 * 
 * @remarks This function serves as a wrapper for AssertDetailed. 
 */
void CheckIgnoreAssert( bool Expression, char * Description, int LineNumber, char * FileName )
{
#if defined(_DEBUG)
    if( !bIgnoreAsserts ) 
    {
        if( AssertDetailed( Expression, Description, LineNumber, FileName ) ) 
        { 
            // Forces the compiler to break
            _asm { int 3 } 
        }
    }
#endif
}

/**
 * An extended assert function which provides more details to the assert
 *
 * @param Expression The expression to be evaluated.
 * @param Description Output describing what values were asserted or why. 
 * @param LineNumber The exact line that triggered the assert. 
 * @param FileName The name of the source file containing the assert.
 */
bool AssertDetailed( bool Expression, char * Description, int LineNumber, char * FileName )
{
#if defined(_DEBUG)
    // TODO: Convert TEXT("The Description should go here") to TEXT(Description) somehow

    // Check the expression like assert
    if( !Expression )
    {
        // This message box tells the user that an assert occurred
        MessageBox( NULL, Description, TEXT("Assert!"), MB_OK );

        // Asks the user if wants to break
        int Result = MessageBox( NULL, TEXT("Would you like to break?"), TEXT("Assert!"), MB_YESNO );

        switch( Result )
        {
        case IDYES:
            return true;
        case IDNO:
            {
                // Give the user the option to ignore asserts forever. 
                int IgnoreForever = MessageBox( NULL, TEXT("Would you like to ignore this assert forever?"), 
                                                                TEXT("Assert!"), MB_YESNO );

                if ( IgnoreForever == IDYES )
                    bIgnoreAsserts = true;

                return false;
            }
        }
	}
#endif

    return false;
}

// EOF
