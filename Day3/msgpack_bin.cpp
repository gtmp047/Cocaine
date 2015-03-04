#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <msgpack.hpp>

int main(int argc , char** argv ){

	
	/*std::make_pair("a",1))
	std::make_pair("b","test");*/
	
	msgpack::sbuffer buff;
	

	if (argc > 2){
		return -1;
	}

	if (std::string(argv[1]).compare("pack") == 0){
		
		std::ofstream myfile;
		myfile.open ("out");
		msgpack::packer<msgpack::sbuffer> packers(&buff);
		packers.pack_map(2);
		packers.pack(std::string("a"));
		packers.pack(1);
		packers.pack(std::string("b"));
		packers.pack(std::string("test"));
		
		std::copy(buff.data(),buff.data()+buff.size(),std::ostreambuf_iterator<char>(myfile));
	}
	else if (std::string(argv[1]).compare("unpack") == 0){

		std::ifstream myfile("out");
		//myfile.open("out");
		std::string buff2;

		myfile.seekg(0,std::ios::end);
		buff2.reserve(myfile.tellg());
		myfile.seekg(0,std::ios::beg);
		buff2.assign(std::istreambuf_iterator<char>(myfile) ,std::istreambuf_iterator<char>());

		msgpack::unpacked unpacks;
		msgpack::unpack(&unpacks,buff2.data(),buff2.length());
		msgpack::object obj(unpacks.get());

		for (int  i = 0; i < obj.via.map.size; ++i)
		{
			std::cout << (obj.via.map.ptr+i)->key << "   "<<(obj.via.map.ptr+i)->val<<std::endl;
		}
	}
	else {
		return -1;
	}


}
