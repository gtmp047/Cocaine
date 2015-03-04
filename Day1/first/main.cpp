#include <cocaine/framework/dispatch.hpp>
#include <string>

class worker_t {
public:
	worker_t(cocaine::framework::dispatch_t &dispatch);

	std::shared_ptr<cocaine::framework::logger_t> logger;

private:
};

class handler_foo_t
	: public cocaine::framework::handler<worker_t>
{
public:
	handler_foo_t(worker_t &worker);
	void on_invoke();
	void on_chunk(const char *chunk, size_t size);
	void on_error(int code, const std::string &message);
	void on_close();
private:
	std::shared_ptr<cocaine::framework::logger_t> logger;
};

worker_t::worker_t(cocaine::framework::dispatch_t &dispatch)
	:logger(dispatch.service_manager()->get_system_logger())
{
	COCAINE_LOG_INFO(logger,"worker starts!");

	dispatch.on<handler_foo_t>("foo", *this);
}

handler_foo_t::handler_foo_t(worker_t &worker)
	:cocaine::framework::handler<worker_t>(worker)
	,logger(worker.logger)
{
	COCAINE_LOG_INFO(logger,"handler foo was created");	
}

void handler_foo_t::on_invoke()
{
	COCAINE_LOG_INFO(logger,"handler foo::on_invoke");	
}

void handler_foo_t::on_chunk(const char *chunk, size_t size)
{
	COCAINE_LOG_INFO(logger,"handler foo::on_chunk");

	response()->write(std::string("Hello World!"));
	response()->close();

	//response()->error(1000, "something is wrong");	
}

void handler_foo_t::on_error(int code, const std::string &message)
{
	COCAINE_LOG_INFO(logger,"handler foo::on_error");	
}

void handler_foo_t::on_close()
{
	COCAINE_LOG_INFO(logger,"handler foo::on_close");	
}

int main(int argc, char **argv)
{
	
	return cocaine::framework::run<worker_t>(argc,argv);
}