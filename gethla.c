#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

static void print_device(libusb_device *dev) {
	struct libusb_device_descriptor desc;
	libusb_device_handle *handle = NULL;
	char string[256];
	int ret;

	ret = libusb_get_device_descriptor(dev, &desc);
	if (ret < 0) {
		fprintf(stderr, "failed to get device descriptor");
		return;
	}
	
	if (0x0483==desc.idVendor) {
	switch (desc.idProduct)	{
	case 0x3748:
		ret = libusb_open(dev, &handle);
		if (LIBUSB_SUCCESS == ret) {
			if (desc.iSerialNumber) {
					ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
					if (ret > 0) {
						printf("STLink V2   hla_serial ");
						for (int i = 0; i < ret; i++) {
							printf("\\x%02X",string[i]);
						}
						printf("\n");
					} else {
						printf("Unable to retrieve serial number.\n");
					}
				}
			}
			break;
		case 0x374b:
			ret = libusb_open(dev, &handle);
					if (LIBUSB_SUCCESS == ret) {
						if (desc.iSerialNumber) {
								ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
								if (ret > 0) {
									printf("STLink V2.1 hla_serial ");
									printf("%s\n",string);
								} else {
									printf("Unable to retrieve serial number.\n");
								}
							}
						}
			break;
		default:
			printf("Device not recognised! (%04X)\n", desc.idProduct);
		}
	}

	if (handle)
		libusb_close(handle);
}

int main(){
	printf("Scanning for connected STLink\n");

	libusb_device **devs;
	ssize_t cnt;
	int r, i;

	r = libusb_init(NULL);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

	for (i = 0; devs[i]; i++)
		print_device(devs[i]);

	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);
}
