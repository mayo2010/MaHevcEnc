#pragma once
#include "unicodemacro.h"
#include <vector>
#include <map>


namespace Utility 
{

	// handy little container for our argument vector
	struct   CmdParam {
		std::vector<tstring> strings_;
	};

	/**
	A utility for parsing command lines.

	This was originally written by Chris Losinger, changes were simply
	removing the inheritance from std::map<>, and adding a map as a member
	variable instead. then all the VCF related String was replaced with 
	tstring and can suite both unicode and non-unicode string

	Example :

	Our example application uses a command line that has two
	required switches and two optional switches. The app should abort
	if the required switches are not present and continue with default
	values if the optional switches are not present.

	Sample command line :
	MyApp.exe -p1 text1 text2 -p2 "this is a big argument" -opt1 -55 -opt2

	Switches -p1 and -p2 are required.
	p1 has two arguments and p2 has one.

	Switches -opt1 and -opt2 are optional.
	opt1 requires a numeric argument.
	opt2 has no arguments.

	Also, assume that the app displays a 'help' screen if the '-h' switch
	is present on the command line.

	\code
#include "cmdline.h"
using namespace Utility;
using namespace std;
void show_help()
{
	tcout<< _T("This is a help string") <<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	CommandLine cmdLine;
	// parse argc,argv
	if (cmdLine.SplitLine(argc, argv) < 1)
	{
		// no switches were given on the command line, abort
		ASSERT(0);
		exit(-1);
	}

	// test for the 'help' case
	if (cmdLine.HasSwitch( _T("-h") ) )
	{
		show_help();
		exit(0);
	}

	// get the required arguments
	tstring p1_1, p1_2, p2_1;
	try
	{
		// if any of these fail, we'll end up in the catch() block
		p1_1 = cmdLine.GetArgument( _T("-p1") , 0);
		p1_2 = cmdLine.GetArgument( _T("-p1") , 1);
		p2_1 = cmdLine.GetArgument( _T("-p2") , 0);

	}
	catch (...)
	{
		// one of the required arguments was missing, abort
		ASSERT(0);
		exit(-1);
	}

	// get the optional parameters

	// convert to an int, default to '-1'
	int iOpt1Val =    tstoi( cmdLine.GetSafeArgument( _T("-optInt"), 0, _T("-1") ).c_str() );
	tcout<<iOpt1Val<<endl;
	return 0;
}
	\endcode
	@version 1.0 Chris Losinger
	@version 2.0 Jim Crafton
	@version 3.0 Marshall Wei
	*/
	class   CommandLine 
	{
	public:
		typedef std::map<tstring, CmdParam> CommandLineMap;
		typedef std::vector<tstring> CommandLineVector;

		CommandLine() {}
		virtual ~CommandLine() {
            for(CommandLineMap::iterator it = m_commandLine.begin(); it != m_commandLine.end(); )
            {
                m_commandLine.erase(it++);
            }

            for(CommandLineVector::iterator it1 = m_originalCommandLine.begin(); it1 != m_originalCommandLine.end(); )
            {
                it1 = m_originalCommandLine.erase(it1);
            }
        }
		/**
		parse the command line into switches and arguments.
		@return int number of switches found
		*/
		int SplitLine( int argc, TCHAR **argv );

		int SplitLine( const tstring& commandLine );

		int SplitLine( const std::vector<tstring>& commandLine );

		/**
		was the switch found on the command line ?
		\code
		ex. if the command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

		call                          return
		----                          ------
		cmdLine.HasSwitch("-a")       true
		cmdLine.HasSwitch("-z")       false
		\endcode
		@return bool true if it has the swith, otherwise false
		*/
		bool HasSwitch( const tstring& aSwitch ) const ;

		/**
		fetch an argument associated with a switch . if the parameter at
		index iIdx is not found, this will return the default that you
		provide.

		example :
		\code
		command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

		call                                      return
		----                                      ------
		cmdLine.GetSafeArgument("-a", 0, "zz")    p1
		cmdLine.GetSafeArgument("-a", 1, "zz")    p2
		cmdLine.GetSafeArgument("-b", 0, "zz")    p4
		cmdLine.GetSafeArgument("-b", 1, "zz")    zz
		\endcode
		*/

		tstring GetSafeArgument(const tstring& aSwitch, size_t iIdx, const tstring& aDefault) const;

		/**
		fetch a argument associated with a switch. throws an exception
		of (int)0, if the parameter at index iIdx is not found.

		example :
		\code
		command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

		call                             return
		----                             ------
		cmdLine.GetArgument("-a", 0)     p1
		cmdLine.GetArgument("-b", 1)     throws (int)0, returns an empty string
		\endcode
		*/
		tstring GetArgument( const tstring& aSwitch, size_t iIdx ) const;

		tstring GetArgument( size_t index ) const;

		/**
		@return the number of arguments found for a given switch. -1 if the
		switch was not found
		*/
		int GetArgumentCount(const tstring& aSwitch) const;

		size_t GetArgCount() const {
			return m_originalCommandLine.size();
		}

		const std::vector<tstring>& GetOriginalCommandLine() const 
		{
			return m_originalCommandLine;
		}
	protected:
		/**
		protected member function
		test a parameter to see if it's a switch :
		switches are of the form : -x
		where 'x' is one or more characters.
		the first character of a switch must be non-numeric!
		*/
		bool IsSwitch(const tstring& param) const;

		CommandLineMap            m_commandLine;
		CommandLineVector         m_originalCommandLine;
	};
    
}
