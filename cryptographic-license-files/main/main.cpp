#include <stdio.h>





extern "C" void fatfsgen_example_mount(void);
extern "C" void fatfsgen_example_unmount(void);


int cryptographic_main(void);

/* Inside a .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main()
{


	fatfsgen_example_mount();


	cryptographic_main();

	fatfsgen_example_unmount();

}
