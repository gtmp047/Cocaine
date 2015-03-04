#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <msgpack.hpp>

int main(){

	std::map<std::string, int> maps;
	maps.insert(std::make_pair("a",1));
	maps.insert(std::make_pair("b",2));

	msgpack::sbuffer buff;
	msgpack::packer<msgpack::sbuffer> packers(&buff);

	packers.pack(maps);

	//std::copy(buff.data(),buff.data()+buff.size(),
	//	std::ostreambuf_iterator<char>(std::cout));

	msgpack::unpacked unpacks;
	msgpack::unpack(&unpacks,buff.data(),buff.size());

	msgpack::object obj(unpacks.get());

	std::map<std::string, int> maps_1;

	obj.convert(&maps_1);

	for(auto id=maps_1.begin(),end=maps_1.end();id!=end;++id){
		std::cout<<id->first<<" "<<id->second<<std::endl;
	}


	return 0;
}