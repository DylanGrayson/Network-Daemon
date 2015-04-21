/* 
This submission is for the following people:
    Conner Swann
    Dylan Grayson
    Brandon Paree
*/


#include "daemon.h"

#define PORT 23001



const char* matt_text[] =
{"                    ...:D88D88DMN8ZD8MONO88D8O8DNDN888... .",                     
"               . ..$~7DNNDOZDDD8N88NN8ODD8O8DNN8NDDN8$O$DZ$...",                  
"               .,:DND8MM88D88NMOND8NDNDND8DODDNM8M8ND8O8DD8N8O  .",               
"            ..8Z~8D88NDN8ND8NDNO8ONNDONOM8D8DNN88N888DNND8NND8ZZ...",             
"        ....7D8NNDNNMNNNND8DDDONDD8NDZ8NDDN8D8Z8DNDNZDMNNOD8DD8O8O....",          
"       .  :ZDDDNNNMMD8DNDD88OODDNDD88DDDDO8DD88DNDDDDDDMN8DDNDDD8D$:..",          
"     ....$Z$O88DNMNZNNN8888DDDDDDDDDD88DNDDDDDD8ODDDNDDDMDD8DNDDDD88O...",        
"      .?$D78O88D8ND88D8NOODDDN88DDDDDNNDDDDDDD8D8DDDNDDDN8N8D8NN8DDDDNI.",        
"  . .,Z8N87$88ZO8D888OO88Z8OO88O8DD8NDNNNDD8DD8O8DDNDNNDD8DD8D8ND8DN8DNO",        
"  ..=ZONZZ$OO88Z8O8O8D88888DDD8888OND8DDDDNDD8NDDDD8DD8DN8DDD8N8N88NDDD88..",     
"   :Z7OZZZZOOD88O8DD88888888OO88888DD8DDDDDNNNDO88DDD88NNN8888MDNNO8N8DDD8.",     
" ..$OZZ$ZZZOZ8DD88D888D8DD88888D8DDNDNDDDDDDDDDNDD888888NND8D8DN8N8O8888888.",   
"..IZIZO$ZZDO8OZZOODDDDDDDNDDDDDD88DNNNNNNDN8DDDDD88D8DDD88NDDDD88NND8888D8Z7.",   
".:I$O$OOO8O88$$ZZZ888DDD88D8D888DDD8DNNNDNNN8DDD8O8OOOOZ88888DDD88DON888$D8O..",  
".~ZZDODZ8ZZ7II??7IZ$Z88D888ZOO88D8DD8DNNNNNDD88OOOOZZZZO88ZO88D8DDDD8D88DZOOZ.",  
".IOOOOOOZI+=====++?I77$ZOZOZZZOO888D88D88888OZZO$$$$$7$$$ZZ8OODDDDNND8D8DOOO8.",  
" ZODZZO$7=~~~~~===++??I777$Z$$$ZZOOOO8OOZZZZ$$$$777777777$$$ZOO8DNDND8D8D8DO8+",  
".$O8OO$I+~~~~~~====++++????7777I$$$$Z$$Z$$77777IIIIIIIIIIII777$Z8DNNN88DDD8ZO?..",
".ZOZO7I?=~~~~~=====++++++++??I?III7777777I777IIIIIIIIIIIIIII?II7Z8DDDD88DO8Z8Z",  
" =8O$7I?=~~~~======++++++++++?????IIIIIIIIIIIIIIIIIIIIIIIIIIIIII$Z88DDODDO8OZZ",  
"  O8$I++~~~~======+++++??+?+?????????II?IIIIIIIIIIIIIII??IIII?II7ZO888D88Z88O$",  
"  OO77I+=~~~====++++++?+?????????I??????III?IIIIIIIIIIIIIIIII?II7$ZO8D888OO8Z,",  
"  ?ZZ7I=======+++?+???????????IIIII????IIIIIIIIIIIIIIIIIIIIIIII7$$O8O8O8OOOZZ.",  
"  ,O$$I+=====+++++++?+?????IIIII7IIIIIIIIIIIIIIIII7IIIIIIIIIIIII7$ZOZ888OOOO?.",  
"  .OO7I+====++++?+++?????II???II?????IIIIIIIII77I777IIIIIIIIII7I7$ZO8OO8ZOZZ~.",  
"  .ZZ$7+===++++++++++???I???III??III?IIIIIIII7777I77IIIIIIIIIII77$ZOOOOO$Z$$,.",  
"   $$$?=====++++++++++???+?????IIIIIIIIIIIIIIIIIIIII7III7IIIIII7$ZZOOOOZZZZ$..",  
"   O7++=====++++++++++??+???I?I?I?I??II?IIIIIIIIIIIIIII77IIIIII7$$OOZOOOOO8$..",  
"  .Z7=========++????+++????II?IIII????I??I??IIIIIIIIIIIIIIIIIIII7ZOZOO8OOO$?.",   
"  .O7=====~==+++++?+?I??I?IIIIIII?????IIIIIIIII7I777777I7IIIIIIIII7$OOOOZO$. .",  
"  .8I=====+I7I?+?I???IIIIII7IIIIIII?II7II77777777777III77IIIIII????IZOO88OO",     
".=?$I====I$$ZOOOZZZ$7777II77III77II77777I7III77777777777II7IIII????IZOO8ZZ.",     
"I++$I=++?7$OOO8888D8OOOZ$7$$77777I7$77777$$$$$77777$777$7III7III???I$Z$OZO.",     
"?O?$+=+?7$$7$$$ZO88DDD88ZZZ$$$7777$Z$$Z$ZZZOOZZZOZZOOOZZOZ$7IIIII??IZOZO$,.?7I?.",
".ZZI==+?7$I7$Z$$$ZZO88888OOZZZ$$$$$ZZZZOO888888DD88888OOOOZZ$77I????$OO$7777IIII",
".Z$?==+?II$O888NMNNNNNDND888OOZ$$$$$OOO88DDDNND888OOOO88O8OZZ$7II???$ZZ7777IZOOO",
".$=I==+??7$$OND$DDD88OZ8DD88Z$7II?I7ZOO8NNNNNMNMMMD8OOZZZZZ$$$$7I???$Z$7II77$OOZ",
".+I?==+++?????I$ZZO$OZZZZZZ$$I????I7$ZO88NNNDNDNDDDDNNND8OZZ$$77I??I$ZI7I77I7ZZ$",
".=I7===+++++?I77$77$$Z8OZZ$7II?+???I7ZZOOOOO8OOO88DDDD888OOO$77III??I$77$7IIIZZ7",
".~?7=====++++?II$$$$Z$$$$7III+++???I7$ZZZOOOO88OZZZOZZZZZ$$$$7IIII????$OOZ$$I$$.",
".:+I+==~==++++?III77777II??+++??III7777$$$$ZZZOOOOZOZZ$Z$$77777III?I??7ZOOZ$7$+.",
".:=+========++??IIIII?????++++++?III77777$77$$$Z$$$$$$7777IIIIIII??I??I$$ZZ$I7..",
"..?~=+++++++++????????????++++++?III7777777$7777$$$77777III7IIIIII????I7$Z7I7...",
"..==+++++?+?++?+++++??????+===++?IIII7777$777I77777777IIIII7IIIII??+?7$$$7I7~.",  
"  ==+++???????++++++???II?+===++?III7I77$$77II7III7II7II7IIIIIIIII???Z$7??Z7..",  
"  ~=+++??????++++++??III7=====+?IIIII7777Z$777II7II7I77I77777III?I???7II?77...",  
"  .==????????++????III77===??I7777777IIII7Z$$7I77IIIIII77777777III??I777??=",     
"  .:~????I???+????III77I?I77777$$$$7777777Z$$$777777I7777777777II???IIIIII.",     
"  ..I????I??+??????III??7ZDDDDZZZZZ8DNNDZZ$$$$$77777777777777777I???7IIII..",     
"     .?II??????????II????I$ZZZOOZZ8OOO88OZ$77$$$777777777777777II??I77II",        
"     .??????????+?7???????III7ZZOZ$ZZZZ$$77777$77777777777I7777II??ZZ7..",        
"     .?III????????I?+?+???III7$$$$$7$$$$77777777$77777777777777II?+",             
"     .?IIII?????I????I??+?77?I7$$$7I777$$$77$7777$$7$777777IIIIII?.",             
"     .+IIIII???IIIII7II777I???IIIIIII777$$$7$$$$$7$7$77777777IIII?",              
"     ..IIIII?IIII77$$$$7I?7$$ZZZZZOOZZZ$77$ZZZZZ$$7Z$77777777III??.",             
"     ..IIIIIIIIII7$ZOZ$$ZZZZZOOOOOOOOOOOOOZ$ZZOZZ$77$777777777II?I.",             
"       :IIIII?II7$ZO8OZO$$ZOZOOO8DDOOOOOZOOD888OZZ$$7$7$$7777III?=.",             
"       .IIIIIIII7777IIII?II7III777777$7$Z$$$$$ZZZZ$$$7$$777777III..",             
"        .7I7I7I7777II?III7III777$$$$$$$$$$$$$$$$$$$7$777777777I7+..",             
"       ..,II77777IIIIIIII77777$ZZZZZZZ$$$$$$7777$$$$$$$$777777$?.",               
"       ...?77777777IIIII7777$$ZZZZZZZZ$$$$$77777$$$$$$$$77777$=..",               
"           ?77$7IIIIIIIII777$$$ZZZZZ$$$$$$$$77777$$$$$$$77$ZZ",                   
"          ..:$$77IIIIIIIII7$$$$$ZZ$$$$$$$$$77777777$$$$$$$O...",                  
"             ,$$$7IIIIIIIIIIIIIIII7777777777$7777$7$$$ZZO7.",                     
"             . $$77IIIII??????IIIIIIIII777777777$$$$ZZO8.",                       
"             . ..O$7IIII???????III7I7I777777$$$$$ZZZO8+..",                       
"                  IZ7I7IIII?IIII777777777$$$$$$$ZZOD8.",                          
"                  . 8$$777777$7$$$$$$$$$$$$Z$ZZO8DD,..",                          
"                    ..O$$$Z$ZZZZOOZZZZZZZZZZO8DDO..."};    




void sig_handler(int signo);
void connection_handler(int * connection);

int main(int argc, char* argv[]) {
    // init daemon
    daemon_init();

	struct sockaddr_in server_address;
	int client_socket, connected, rc;
	socklen_t sin_size;
	
	bzero(&server_address, sizeof(server_address));
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);

    /* Thread Stuff */
    //create, initialize, and set the thread attribute
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t threads[100];


    syslog(LOG_NOTICE, "Matt Daemon: Okay, setting myself up.");
    for(int i=0; i<69; i++){
        syslog(LOG_NOTICE, matt_text[i]);
    }
	if(bind(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
		perror("error connecting\n");
		exit(EXIT_FAILURE);
	}
	
	listen(client_socket, 5);

    // loop forever
    int threadct = 0;
    while (1){
		struct sockaddr_in client_address;
		sin_size = sizeof(client_address);
        // wait for connections
		connected = accept(client_socket, (struct sockaddr *)&client_address, &sin_size);
		if (connected < 0) 
          perror("ERROR on accept");

        syslog(LOG_NOTICE, "Matt Daemon: Forking a thread for the new connection");
        rc = pthread_create(&threads[threadct++], &attr, (void *)connection_handler, (int *)&connected);
        if(rc){
            syslog(LOG_NOTICE, "ERROR; return code from pthread_create() is %d\n", rc);
        }
		
        if (signal(SIGUSR1, sig_handler) == SIG_ERR)
            syslog(LOG_NOTICE, "\ncan't catch SIGUSR1\n");
    }
    close(client_socket);
    return EXIT_SUCCESS;
}

// connection handler
void connection_handler(int * connection){
    char buffer[256];
    int n;
    int con = *connection;
    syslog(LOG_NOTICE, "Entered new connection_handler thread.");
    while(1) {
        //syslog(LOG_NOTICE, "Zeroing Buffer.");
        bzero(buffer, 256);
        syslog(LOG_NOTICE, "Reading from socket. %d", con);
        n = read(con, buffer, 255);

        if (n < 0)
            perror("ERROR reading from socket");
        if(buffer[0] == 'q') {
            syslog(LOG_NOTICE, "Recieved 'q' from client, killing thread");
            break;
        }
        n = write(con, buffer, 18);
    }
    close(con);
    pthread_exit(NULL);
}

// signal handler
void sig_handler(int signo){
    // if the signal matches, kill
    if (signo == SIGUSR1)
        daemon_exit();
}
