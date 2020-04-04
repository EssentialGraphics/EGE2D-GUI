#include <egeConfig.h>

#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

std::string globalExePath;

void setexepath(std::string path){
    globalExePath=path; 
}

// path with filename
std::string getexepath()
{
	char result[ PATH_MAX ];
	
	#ifdef EGE_LINUX
		ssize_t	count = readlink( "/proc/self/exe", result, PATH_MAX );
	#else	
		ssize_t	count = NULL;
	#endif	
		
	return std::string( result, (count > 0) ? count : 0 );
}

// path only without filename(executable)
std::string getpathonly(){
    string path=getexepath();
    
    int pos=path.find_last_of("/");
    
	#ifdef EGE_LINUX
		return path.substr(0,pos);
	#endif

        #ifdef EGE_WIN64
            // return "C:/projects/EGE2D-GUI-master/samples/scadatank";
            //  return "C:/projects/EGE2D-GUI-master/samples/tutorials/tutorial-02";
            //return "C:/projects/EGE2D-GUI-master/samples/tutorials/tutorial-03";  
            
            return globalExePath;
            
            
        #endif    
}
