# Compile a cross-binutils and cross-compiler

This is my personal note, still not finished yet.

# Works to do first

1. Install VMWare Workstation 12, and pick a flavor of Ubuntu you like. (If you pick
Ubuntu LTS 14.04, I believe you don't need to manually install VMWare Tools.)
2. Run `sudo apt-get install build-essential` to get gcc-4.8 and tools like that.

Now the system is now ready to build the cross-binutils and cross-compiler

# Build a cross-binutils

1. Download [Lastest Binutils](http://ftp.gnu.org/gnu/binutils/ "GUN FTP server")
from the link.
2. Open a terminal and `cd` into the directory you saved your downloaded file in.
run `tar –zxvf FILENAME`, replace __FILENAME__ with the name of the file that you
are going to decompress. You can use `tar --help` to read about what `-zxvf` means.
3. After decompressing, `cd` into the decompressed folder.
4. Run `./configure --prefix=/foo --target=arm-elf`, where `prefix` means the
folder to store your compiler(replace `foo` with the absolute path of the folder you
just created), `target` means your targeted machine's environment.
    * P.S. If you encountered `configure: error: C compiler cannot create executables`,
    please run `sudo apt-get install build-essential` beforehand.
5. Run `make` and `sudo make install` afterwards. (Use `sudo` if permission error occured)

#  Build a cross-compiler

1. Download [Lastest compiler](http://ftp.gnu.org/gnu/gcc/gcc-5.2.0/) "GUN FTP server")
from the link.
2. Open a terminal and `cd` into the directory you saved your downloaded file in.
run `tar –zxvf FILENAME`, replace __FILENAME__ with the name of the file that you
are going to decompress. You can use `tar --help` to read about what `-zxvf` means.
3. After decompressing, `cd` into the decompressed folder.
4.
