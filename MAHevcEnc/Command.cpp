#include "Command.h"


using namespace std;

namespace Utility
{
    int CommandLine::SplitLine( const std::vector<tstring>& commandLine )
	{
		m_commandLine.clear();
		m_originalCommandLine.clear();

		m_originalCommandLine = commandLine;

		tstring curParam; // current argv[x]
		size_t argc = m_originalCommandLine.size();
		// skip the exe name (start with i = 1)
		for (size_t i = 1; i < argc; i++)  {
			// if it's a switch, start a new CommandLine
			if ( IsSwitch(m_originalCommandLine[i]))  {
				curParam = m_originalCommandLine[i];

				tstring arg;

				// look at next input tstring to see if it's a switch or an argument
				if (i + 1 < argc)  {
					if (!IsSwitch(m_originalCommandLine[i + 1])) {
						// it's an argument, not a switch
						arg = m_originalCommandLine[i + 1];

						// skip to next
						i++;
					}
					else {
						arg = _T("");
					}
				}

				// add it
				CmdParam cmd;

				// only add non-empty args
				if (arg != _T("") )  {
					cmd.strings_.push_back(arg);
				}

				// add the CmdParam to 'this'
				std::pair<CommandLineMap::iterator, bool> res = m_commandLine.insert(CommandLineMap::value_type(curParam, cmd));

			}
			else  {
				// it's not a new switch, so it must be more stuff for the last switch

				// ...let's add it
				CommandLineMap::iterator theIterator;

				// get an iterator for the current param
				theIterator = m_commandLine.find(curParam);
				if (theIterator!=m_commandLine.end())  {
					(*theIterator).second.strings_.push_back(m_originalCommandLine[i]);
				}
				else  {
					// ??
				}
			}
		}

		return static_cast<int>( m_commandLine.size() );
	}


	int CommandLine::SplitLine( int argc, TCHAR **argv )
	{
		std::vector<tstring> args;

		for ( int j=0;j<argc;j++ ) {
			args.push_back( tstring(argv[j]) );
		}

		return SplitLine( args );
	}

	int CommandLine::SplitLine( const tstring& commandLine )
	{
		std::vector<tstring> args;
		const TCHAR* P = commandLine.c_str();
		const TCHAR* start = P;
		const TCHAR* argStart = P;

		int sz = static_cast<int>( commandLine.size() );
		while ( (P - start) < sz ) {
			if ( *P == '\"' ) {
				P++;
				while ( ((P - start) < sz) && (*P != '\"' ) ) {
					P++;
				}
				P++;
			}

			if ( *P == '\"' ) {
				continue; //loop again
			}

			if ( *P == ' ' ) {
				//argument
				//strip out begin/end quotes

				tstring arg;
				const TCHAR* tmpArgStart = argStart;
				const TCHAR* tmpArgEnd = tmpArgStart;
				while ( tmpArgEnd < P ) {
					if ( *tmpArgEnd == '\"' ) {
						if ( tmpArgStart != tmpArgEnd ) {
							arg.append( tmpArgStart, tmpArgEnd - tmpArgStart );
							tmpArgStart = tmpArgEnd;
						}
						tmpArgStart++;					
					}

					tmpArgEnd ++;
				}

				if ( arg.empty() ) {
					arg.append( tmpArgStart, tmpArgEnd - tmpArgStart );
				}

				args.push_back( arg );

				while ( (*P == ' ') && ((P - start) < sz) ) {
					P++;
				}
				argStart = P;
				P--;
			}

			P++;
		}
		if ( argStart < P ) {
			tstring arg;
			arg.assign( argStart, P-argStart );
			args.push_back( arg );
		}

		return SplitLine( args );
	}


	bool CommandLine::IsSwitch(const tstring& aParam) const
	{
		if (aParam.empty())
			return false;

		// switches must non-empty
		// must have at least one character after the '-'

		if (aParam.size() <= 1)  {
			return false;
		}

		// switches always start with '-'
		if (aParam[0]=='-')   {
			// allow negative numbers as arguments.
			// ie., don't count them as switches
			return (!isdigit(aParam[1]));
		}
		else   {
			return false;
		}
	}


	bool CommandLine::HasSwitch(const tstring& aSwitch) const
	{
		CommandLineMap::const_iterator theIterator;
		theIterator = m_commandLine.find(aSwitch);
		return (theIterator != m_commandLine.end());
	}


	tstring CommandLine::GetSafeArgument(const tstring& aSwitch, size_t index, const tstring& defaultVal) const
	{
		tstring result;

		if ( !defaultVal.empty() ) {
			result = defaultVal;
		}

		try
		{
			result = GetArgument(aSwitch, index);
		}
		catch (...)
		{
		}

		return result;
	}


	tstring CommandLine::GetArgument( size_t index ) const
	{
		tstring result;
		if ( (index >= 0) && (index < m_originalCommandLine.size()) ) {
			result = m_originalCommandLine[index];
		}
		return result;
	}

	tstring CommandLine::GetArgument( const tstring& aSwitch, size_t index )const 
	{
		if ( HasSwitch( aSwitch ) )
		{
			CommandLineMap::const_iterator theIterator = m_commandLine.find(aSwitch);
			if (theIterator!=m_commandLine.end())
			{
				if ((*theIterator).second.strings_.size() > index)
				{
					return (*theIterator).second.strings_[index];
				}
			}
		}

		throw (int)0;

		return _T("");
	}


	int CommandLine::GetArgumentCount(const tstring& aSwitch) const
	{
		int result = -1;

		if ( HasSwitch(aSwitch) )  {
			CommandLineMap::const_iterator theIterator = m_commandLine.find( aSwitch );
			if (theIterator!=m_commandLine.end())      {
				result = static_cast<int>( (*theIterator).second.strings_.size() );
			}
		}

		return result;
	}
}