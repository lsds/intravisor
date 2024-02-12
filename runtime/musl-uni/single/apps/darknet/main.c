#include <stdio.h>
#include <stdlib.h>

extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);

int argc = 5;

#if 1
//old
char *argv[] = {"darknet", "classify", "/alexnet.cfg", "/alexnet.weights", "/dog.jpg", NULL};
#define ROOT_CPIO	"root.cpio"
#endif

//1GB

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/alexnet.cfg", "/alexnet.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_alexnet.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/darknet.cfg", "/darknet.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_darknet.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/darknet19.cfg", "/darknet19.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_darknet19.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/darknet53.cfg", "/darknet53.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_darknet53.cpio"
#endif


#if 0
//ok
char *argv[] = {"./darknet", "classify", "/extraction.cfg", "/extraction.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_extraction.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/resnet18.cfg", "/resnet18.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnet18.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/resnet34.cfg", "/resnet34.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnet34.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/resnet50.cfg", "/resnet50.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnet50.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/resnet101.cfg", "/resnet101.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnet101.cpio"
#endif

#if 0
//ok
char *argv[] = {"./darknet", "classify", "/resnext50.cfg", "/resnext50.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnext50.cpio"
#endif

// 4GB

#if 0
//ok on 4GB
char *argv[] = {"./darknet", "classify", "/vgg-16.cfg", "/vgg-16.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_vgg-16.cpio"
#endif

#if 0
//works with 4GB, strange result
char *argv[] = {"./darknet", "classify", "/yolov3-tiny.cfg", "/yolov3-tiny.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_yolov3-tiny.cpio"
#endif

#if 0
//ok on 4GB
char *argv[] = {"./darknet", "classify", "/darknet53_448.cfg", "/darknet53_448.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_darknet53_448.cpio"
#endif

#if 0
//ok on 4GB
char *argv[] = {"./darknet", "classify", "/resnet152.cfg", "/resnet152.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnet152.cpio"
#endif

#if 0
//ok on 4GB
char *argv[] = {"./darknet", "classify", "/resnext152-32x4d.cfg", "/resnext152-32x4d.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnext152-32x4d.cpio"
#endif

#if 0
//ok on 4gb
char *argv[] = {"./darknet", "classify", "/resnext101-32x4d.cfg", "/resnext101-32x4d.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_resnext101-32x4d.cpio"
#endif

#if 0
//ok on 4gb (was segfault)
char *argv[] = {"./darknet", "classify", "/densenet201.cfg", "/densenet201.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_densenet201.cpio"
#endif

// OOM <= 4GB

#if 0
//OOM at 4GB
char *argv[] = {"./darknet", "classify", "/tiny.cfg", "/tiny.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_tiny.cpio"
#endif


#if 0
//OOM at 4GB
char *argv[] = {"./darknet", "classify", "/yolov3.cfg", "/yolov3.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_yolov3.cpio"
#endif

#if 0
//OOM at 4GB
char *argv[] = {"./darknet", "classify", "/darknet19_448.cfg", "/darknet19_448.weights", "dog.jpg", NULL};
#define ROOT_CPIO	"root_darknet19_448.cpio"
#endif




void app_main() {
	printf("app main\n");


	long size = host_get_cpio_size(ROOT_CPIO);

	__intcap_t *cpio = malloc(size);

	long size2 = host_load_cpio(ROOT_CPIO, cpio, size);
	printf("size2 = %d, size = %d\n", size2, size);

	copy_cpio((__intcap_t *) cpio);

	free(cpio);

	extern int main(int argc, char **argv);
	main(argc, argv);
}