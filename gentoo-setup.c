#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define EAX 100
#define MBR "mbr"
#define GPT "gpt"

void baseSystem_Setup(int profile) {

                switch(profile) {

                        case 1:
                                system("eselect profile set 1");
                                system("emerge --ask --verbose --update --deep --newuse @world");
                                //Base
                        break;

                        case 2:
                                system("eselect profile set 5");
                                system("emerge --ask --verbose --update --deep --newuse @world");
                                //Desktop
                        break;

                        case 3:
                                system("eselect profile set 8");
                                system("emerge --ask --verbose --update --deep --newuse @world");
                                //kde

                        break;

                        case 4:
                                system("eselect profile set 6");
                                system("emerge --ask --verbose --update --deep --newuse @world");

                        break;

                        default:
                                printf("Operation Error. Pls Try Again...\n\n");

                        break;

                                char eu[25] = "Europe";
                                char ist[25] = "Istanbul";

                        //timezone and locale
                        system("echo 'Europe/Istanbul > /etc/timezone'  ");
                        system("emerge --config sys-libs/timezone-data");

                                //locale
                                        system("vim /etc/locale.gen");
                                        system("locale-gen");
                                        system("eselect locale set 4");
                                        system("env-update && source /etc/profile && export PS1='(chroot) ${PS1}'");

                        printf("Base System Installation is Successfull!\n");
                }
}

void kernelSetup(char choose[EAX]) {

        //tools
        system("emerge --ask --autounmask linux-firmware pciutils genkernel dhcpcd gentoolkit");
        system("etc-update");
        system("emerge --ask --autounmask linux-firmware pciutils genkernel dhcpcd gentoolkit");
                system("eselect kernel set 1");

                char genkernel[EAX] = "genkernel";
                        int ret = strcmp(choose, genkernel);

                        if (choose == 0) {

                                system("vim /etc/fstab");
                                system("genkernel all");
                        } 
                        else {

                                system("cd /usr/src/linux");
                                system("make menuconfig");
                                system("make && make_modules install");
                                system("make install");

                                        //install initfsram
                                        system("emerge --ask sys-kernel/dracut");
                                        system("dracut --kver=");
                        }
                
}

void systemConfigure() {

        system("emerge --ask app-admin/elogind && rc-update add sysklogd default");
        system("emerge --ask wpa_supplicant");
        system("passwd");

        printf("Pls set Network Configure, hostname and hosts\n\n");
        printf("Operation is Successfull!\n\n");
}


void grubInstall(char type[EAX]) {

        int retgpt = strcmp(type, GPT);

                        //Install grub

                if (retgpt == 0) {

                 system("echo GRUB_PLATFORMS='efi-64' >> '/etc/portage.make.conf'");
                 printf("gpt!\n\n");
                        system("emerge --ask --verbose sys-boot/grub");
                        system("grub-install --target=x86_64-efi --efi-directory=/boot");
                } 
                else {
                        printf("mbr!\n\n");
                        system("emerge --ask sys-boot/grub");
                        system("grub-install /dev/sda");
                }

                        //Configure grub
                        system("grub-mkconfig -o /boot/grub/grub.cfg");

                        printf("Grub install and Configure Operation is Successfull!\n\n");
}



int main() {

                int slct;

                printf("<--------------------->\n\n");

                printf("1-Base System Install\n");
                printf("2-Kernel Install and Configure");
                printf("3-System Configure\n");
                printf("4-Grub install and Configure\n\n");

                printf("<--------------------->\n\n");


                printf("Select a Operation: ");
                scanf("%d", &slct);

                switch(slct) {

                        case 1:
                                int selectprofile;

                                printf("-----------\n\n");
                                printf("1-Base\n");
                                printf("2-Desktop\n");
                                printf("3-Gnome\n");
                                printf("4-Kde\n\n"); 
                                printf("-----------\n\n");

                                        printf("Select a Profile: ");
                                        scanf("%d", &selectprofile);

                                        baseSystem_Setup(selectprofile);

                        break;

                        case 2:
                                printf("---------------\n\n");
                                printf("Genkernel\n");
                                printf("Manual Option\n\n");
                                printf("---------------\n\n");

                                        char kernel[EAX];
                                        printf("Select a Operation: ");
                                        gets(kernel);

                                                kernelSetup(kernel);

                        break;

                        case 3:
                                systemConfigure();

                        break;

                        case 4:
                                char diskType[EAX];
                                        printf("Enter your Disk Type: ");
                                        gets(diskType);

                                        grubInstall(diskType);

                        break;


                }
}