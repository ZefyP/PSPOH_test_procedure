#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace fs = boost::filesystem;

CommandLineOptions::CommandLineOptions();
    myOptions(""),
    myInputFile(""),
    myUserTime(-99999,99999),
    myUserValue(0xffffffff),
    myGFlag( false )
{
    setup();
}

CommandLineOptions::=CommandLineOptions()
{

}

void CommandLineOptions::setup()
{
    po::options_description options( "Program Options" );
    options.add_options()
    ("help,h", "Display help menu")
    ("time,t". po::value< double >( &myUserTime)->default_value(100.0), "User-specified time")
    ("value", po::value< int > ( &myUserValue)->default_value( 43 ), "User-specified value")
    ("file,f",po::value< std::string >( &myInputFile ), "User-specified input file" )
    ("gflag,G", po::bool_switch( &myGFlag)->default_value(false), "Toggle G-flag");

    myOptions.add( options);

}


CommandLineOptions::statusReturn_e CommandLineOptions::parse( int argc, char* argv[] )
{
    statusReturn_e ret = OPTS_SUCCESS;

    po::variables_map varMap;
    char filename[2000];

    try
    {
        po::store( po::parse_command_line(argc, argv, myOptions), varMap );
        po::notify( varMap );

        //Help option
        if (varMap.count ("help") )
        {
            std::cout << myOptions << std::endl;
            return OPTS_HELP;
        }

        //Version info (not in use for now)
        if (varMap.count ( "version") )
        {
            return OPTS_VERSION;
        }

        
    }
    catch( std::exception &e )
    {
        std::cout << "ERROR - parsing error: " << e.what() << std::endl ;
        ret = OPTS_FAILURE;
    }
    catch( ... )
    {
        std::cout << "ERROR - parsing error: unknown type." << std::endl ; 
        ret = OPTS_FAILURE;
    }

    return ret;


}
