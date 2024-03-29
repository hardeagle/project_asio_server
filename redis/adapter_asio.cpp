#include "adapter_asio.h"

redisBoostClient::redisBoostClient(boost::asio::io_context& ioc,redisAsyncContext* rac)
	: context_(rac)
	, socket_(ioc)
	, read_requested_(false)
	, write_requested_(false)
	, read_in_progress_(false)
	,write_in_progress_(false) {
	/*this gives us access to c->fd*/
	redisContext *rc = &(rac->c);

	/*hiredis already connected
	 *use the existing native socket
	 */
	socket_.assign(boost::asio::ip::tcp::v4(), rc->fd);

	/*register hooks with the hiredis async context*/
	rac->ev.addRead = call_C_addRead;
	rac->ev.delRead = call_C_delRead;
	rac->ev.addWrite = call_C_addWrite;
	rac->ev.delWrite = call_C_delWrite;
	rac->ev.cleanup = call_C_cleanup;

	/*C wrapper functions will use this pointer to call class members.*/
	rac->ev.data = this;
}

void redisBoostClient::operate() {
    try {
        if(read_requested_ && !read_in_progress_) {
            read_in_progress_ = true;
            socket_.async_read_some(boost::asio::null_buffers(),
                            boost::bind(&redisBoostClient::handle_read,this,boost::asio::placeholders::error));
        }

        if(write_requested_ && !write_in_progress_) {
            write_in_progress_ = true;
            socket_.async_write_some(boost::asio::null_buffers(),
                            boost::bind(&redisBoostClient::handle_write,this,boost::asio::placeholders::error));
        }
    } catch(...) {
    }
}
	
void redisBoostClient::handle_read(boost::system::error_code ec) {
	read_in_progress_ = false;
	if(!ec) {
		redisAsyncHandleRead(context_);
	}

        if (!ec || ec == boost::asio::error::would_block)
	        operate();
}

void redisBoostClient::handle_write(boost::system::error_code ec) {
	write_in_progress_ = false;
	if(!ec) {
		redisAsyncHandleWrite(context_);
	}

	if (!ec || ec == boost::asio::error::would_block)
		operate();
}

void redisBoostClient::add_read() {
	read_requested_ = true;
	operate();
}

void redisBoostClient::del_read() {
	read_requested_ = false;
}

void redisBoostClient::add_write() {
	write_requested_ = true;
	operate();
}

void redisBoostClient::del_write() {
	write_requested_ = false;
}

void redisBoostClient::cleanup() {
	/*Do I even need this?*/
	printf("cleanup called...\n");	
}

static inline redisBoostClient * cast_to_client(void *privdata) {
	assert(privdata);
	return static_cast<redisBoostClient *>(privdata);
}

/*wrappers*/
extern "C" void call_C_addRead(void *privdata) {
	cast_to_client(privdata)->add_read();
}

extern "C" void call_C_delRead(void *privdata) {
	cast_to_client(privdata)->del_read();
}

extern "C" void call_C_addWrite(void *privdata) {
	cast_to_client(privdata)->add_write();
}

extern "C" void call_C_delWrite(void *privdata) {
	cast_to_client(privdata)->del_write();
}

extern "C" void call_C_cleanup(void *privdata) {
	cast_to_client(privdata)->cleanup();
}
/*end of wrappers*/
