#include <Syringe/Syringe.h>
#include <iostream>

using namespace std;
int main(int argc, char **args) {
	int exploitCount = 0;
	int i = 0;
	iDeviceTarget device;
	char *build = NULL;
	try {
		if (argc > 1) {
			for (i = 1; i < argc; i++) {
				if (!strcmp(args[i], "--device") || !strcmp(args[i], "-d")) {
					i++;
					if (!strcmp("2G", args[i])) {
						device = iD_2G;
					} else if (!strcmp(args[i], "IPT")) {
						device = iD_IPT;
					} else if (!strcmp(args[i], "3G")) {
						device = iD_3G;
					} else if (!strcmp(args[i], "IPT2G")) {
						device = iD_IPT2G;
					} else if (!strcmp(args[i], "3GS_OLD")) {
						device = iD_3GS_OLD;
					} else if (!strcmp(args[i], "3GS_NEW")) {
						device = iD_3GS_NEW;
					} else if (!strcmp(args[i], "IPT3G")) {
						device = iD_IPT3G;
					} else if (!strcmp(args[i], "A4")) {
						device = iD_A4;
					} else if (!strcmp(args[i], "IPAD2")) {
						device = iD_IPAD2;
					} else if (!strcmp(args[i], "IPT4G")) {
						device = iD_IPT4G;
					} else {
						i--;
						cout << "Invalid option for " << args[i] << endl;
						cout << "Valid options are:" << endl;
						cout << "\t2G      - iPhone 2G" << endl;
						cout << "\tIPT     - iPod Touch (first gen)" << endl;
						cout << "\t3G      - iPhone 3G" << endl;
						cout << "\tIPT2G   - iPod Touch (second gen)" << endl;
						cout << "\t3GS_OLD - iPhone 3GS (old bootrom)" << endl;
						cout << "\t3GS_NEW - iPhone 3GS (new bootrom)" << endl;
						cout << "\tIPT3G   - iPod Touch (thrid gen)" << endl;
						cout << "\tA4      - Any A4 device (iPhone 4, iPad)" << endl;
						cout << "\tIPAD2   - iPad 2" << endl;
						cout << "\tIPT4G   - iPod Touch (fourth gen)" << endl;
						return 0;
					}
				} else if (!strcmp(args[i], "--build") || !strcmp(args[i], "-b")) {
					i++;
					build = args[i];
				}
			}
		}
		Syringe *injector;
		if (i > 0) {
			i = 0;
			injector = new Syringe(device, build);
		} else {
			injector = new Syringe();
			char *devinfo = injector->getConnectedDeviceInfo();
			cout << "Found Device \"" << devinfo << "\" in Normal Mode" << endl;
		}
		exploitCount = injector->preloadExploits();
		if (exploitCount > 1) {
			cout << "Please select an exploit:" << endl;
			for (i = 0; i < exploitCount; i++) {
				cout << "\t" << (i + 1) << ". " << injector->getExploitName(i) << endl;
			}
			cout << "> ";
			cin >> i;
			i--;
		} else {
			i = 0;
		}
		cout << "Loading " << injector->getExploitName(i) << "..." << endl;
		injector->loadExploit(i);
		ExploitType eType = injector->getExploitType();
		if (eType == eBOOTROM) {
			cout << "Please put your device in DFU mode..." << endl;
		} else if (eType == eIBOOT) {
			cout << "Please put your device in Recovery mode..." << endl;
		}
		while (!injector->deviceIsReady()) {
			sleep(1);
		}
		cout << "Injecting..." << endl;
		injector->inject(U_IBSS_ONLY);
		cout << "Done!" << endl;
	} catch (SyringeBubble &bubble) {
		cout << bubble.getError() << endl;
	}
	return 0;
}

