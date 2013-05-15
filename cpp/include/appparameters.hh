/*
 * appparameters.hh
 *
 *  Created on: Apr 9, 2013
 *      Author: paul
 *
 *  Description:  Contains header definition for the AppParameters class.
 */

#ifndef APP_PARAMETERS_HH
#define APP_PARAMETERS_HH

namespace MakerBot {

/*
 * This class is a light wrapper for the parameters provided to an application's main() entry point.
 *
 * Note:  This class may be extended at some point to provide parsed, dictionary-based lookup of
 *        command line arguments.
 */
class AppParameters {
public:

	/*
	 * Default Constructor.
	 */
	AppParameters() :
		m_argc(0),
		m_argv(NULL){

	}

	/*
	 * Alternate constructor.  Initializes all members.
	 */
	AppParameters(int argc, char* argv[]) :
		m_argc(argc),
		m_argv(argv)
	{;}
	
	/*
	 * Destructor.
	 */
	virtual ~AppParameters(){;}
		
	// Members.  Left public (for now) for ease of use.
	int m_argc;
	char** m_argv;
};


}

#endif // APP_PARAMETERS_HH
