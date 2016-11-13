#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<iostream>
#include<map>
#include<chrono>
#include<thread>

struct player final{
	explicit player(const char* aup,const std::size_t& volume=0)noexcept
		:err_flag(!(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)<0))
	{
		if(err_flag){
			Mix_Init(0);
			talk=Mix_LoadMUS(aup);
			if(talk==nullptr)std::cerr<<Mix_GetError()<<std::endl;
			else{if(volume)Mix_VolumeMusic(volume);}
		}
	}
	~player()
	{
		if(err_flag)Mix_FreeMusic(talk);
	}
private:
	template<class Chrono>
	void play(Chrono&& ch)const noexcept
	{
		if(err_flag){
			if(-1==Mix_PlayMusic(talk,-1)){
				std::cerr<<Mix_GetError()<<std::endl;
			}else{
				std::this_thread::sleep_for(std::forward<Chrono>(ch));
				Mix_HaltMusic();
			}
		}
	}

	const bool err_flag=false;
	Mix_Music* talk=nullptr;
public:
	inline void dot()const noexcept{play(std::chrono::microseconds(150000));}
	inline void dash()const noexcept{play(std::chrono::microseconds(400000));}
	inline void space()const noexcept{std::this_thread::sleep_for(std::chrono::microseconds(50000));}
};

std::map<char,std::string> make_morse_table()
{
	return std::map<char,std::string>{
		{'a',"102"},
		{'b',"20010101"},
		{'c',"2010201"},
		{'d',"20101"},
    		{'e',"1"},
	   	{'f',"10102001"},
	   	{'g',"20201"},
    		{'h',"1010101"},
    		{'i',"101"},
    		{'j',"1020202"},
    		{'k',"20102"},
    		{'l',"1020101"},
    		{'m',"202"},
	   	{'n',"201"},
		{'o',"2002002"},
		{'p',"1020201"},
    		{'q',"2020102"},
    		{'r',"10201"},
    		{'s',"10101"},
    		{'t',"2"},
    		{'u',"10102"},
    		{'v',"1010102"},
    		{'w',"10202"},
	   	{'x',"2010102"},
   		{'y',"2010202"},
	   	{'z',"2020101"},
	   	{'1',"102020202"},
	   	{'2',"101020202"},
	   	{'3',"101010202"},
	   	{'4',"101010102"},
	   	{'5',"101010101"},
		{'6',"201010101"},
    		{'7',"202010101"},
	   	{'8',"202020101"},
	   	{'9',"202020201"},
    		{'0',"202020202"},
    		{'.',"10201020102"},
    		{',',"20201010202"},
    		{'?',"10102020101"},
    		{'!',"20102010202"},
    		{'-',"20101010102"},
    		{'/',"201010201"},
    		{'@',"10202010201"},
    		{'(',"201020201"},
    		{')',"20102020102"},
    		{' ',"0"}
	};
}

int main(int argc,char** argv)
{
	auto mrs=make_morse_table();
	std::string s;

	std::cout<<">> ";
	std::cin>>s;

	player pl("beep.wav",32);
	for(const auto& c:s){
		for(const auto& c:mrs[c]){
			switch(c){
				case '2':
					pl.dash(); break;
				case '1':
					pl.dot(); break;
				case '0':
					pl.space(); break;
			}
		}
		std::this_thread::sleep_for(std::chrono::microseconds(300000));
	}
}
