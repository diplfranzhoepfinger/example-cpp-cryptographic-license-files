#include <stdio.h>





extern "C" void spiffsgen_example_mount(void);
extern "C" void spiffsgen_example_unmount(void);


int cryptographic_main(void);

/* Inside a .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main()
{


	spiffsgen_example_mount();


	cryptographic_main();

	spiffsgen_example_unmount();

}
