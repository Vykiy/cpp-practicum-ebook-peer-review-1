#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
 
using namespace std::string_literals;
 
static int MAX_PAGES = 1000;
static int MAX_USERS = 100000;
 
class Reader {
public:
	Reader() : user_pages_(MAX_USERS),users_on_page_(MAX_PAGES){}
 
	void Read(int id, int page)
	{
		if (user_pages_[id] == 0)
		{
			user_pages_[id] = page;
			++users_num_;
		}
		else
		{
			--users_on_page_[user_pages_[id]];
			user_pages_[id] = page;
		}
		++users_on_page_[page];
 
	}
 
	double Cheer(int id) const
	{
		double result = 0;
		int count = 0;
 
		if (users_num_ == 1 && user_pages_[id] != 0) {
			result = 1;
		}
		else if (user_pages_[id] == 0)
		{
			result = 0;
		}
		else
		{
			for (int i = 1; i < user_pages_[id]; ++i)
			{
				if (users_on_page_[i] != 0) {
					count += users_on_page_[i];
				}
			}
			result = count / static_cast<double>(users_num_ - 1);
		}
		return result;
	}
 
private:
	int users_num_ = 0;
	std::vector<int> user_pages_;
	std::vector<int> users_on_page_;
};
 
void ProcessingRequests(Reader& reader, std::istream& in, std::ostream& out)
{
	std::string request;
	int count_request;
	in >> count_request;
	for (int i = 0; i < count_request; ++i)
	{
		in >> request;
		if (request == "READ"s)
		{
			int id, page;
			in >> id >> page;
			reader.Read(id, page);
		}
		else if (request == "CHEER")
		{
			int id;
			in >> id;
			out << std::setprecision(6) << reader.Cheer(id) << std::endl;
		}
	}
}
 
int main()
{
	Reader reader;
	ProcessingRequests(reader, std::cin, std::cout);
}