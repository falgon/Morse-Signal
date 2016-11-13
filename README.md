# Morse-Signal
This tool convert an input alphanumeric character into Morse code

## How to
1. Please get the Music file from ポケットサウンド
  Here: http://pocket-se.info/archives/356/
 
2. Renaming & Converting to beep.wav from alert2.mp3

3. Replacing to under the More-Signal/src/ directory

4. Compiling & Runnig

For Brew
```sh
$ brew install sdl_mixer
```
 For Linux
```sh
$ sudo apt-get install build-essential
$ wget -O SDL_mixer-1.2.12.tar.gz http://goo.gl/o0GIX
$ tar -xzvf SDL_mixer-1.2.12.tar.gz -C ~/ && cd SDL_mixer-1.2.12
$ ./configure && make
$ sudo make install
```
Compile & Run
```sh
$ clang++ morse.cpp $(sdl-config --cflags --libs) -lSDL -lSDL_mixer
$ ./a.out
>> [input your favorite words :)]
```
Enjoy! :)

## Music file
Thanks to <a href="http://pocket-se.info/archives/356/">ポケットサウンド:【効果音】警告音　ビー</a>
