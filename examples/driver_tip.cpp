#include <iostream>
using std::cout;
#include <iomanip>
using std::quoted;

#include "../tip/tip.h"

/// Trim all path content up to the last '/' to get the filename only.
auto STRIP_PATH= [](const std::string &s)->std::string {
    size_t end = s.find_last_of("/");
    return (end == std::string::npos) ? s : s.substr(end+1, std::string::npos);
};

int main(int argc, char *argv[]){
    if(argc!=2){
        std::cout << ">>> Missing INI file!\n"
                     "Usage:\n"
                     "   " << STRIP_PATH(argv[0]) << " <ini_file>\n\n";
        return 1;
    }


    // [1]== Create the INI parser and read the content from file.
    TIP reader(argv[1]);
    // Check for any parser error.
    if(not reader.parsing_ok()){
        std::cerr << ">> Sorry, parser failed with message: " 
                  << reader.parser_error_msg()
                  << "\n";
        return 1;
    }



    // [2]== RETRIEVE DATA.
    auto sections = reader.get_sections_list();
    for(const auto& sec_name : sections){
        auto fields = reader.get_fields_list(sec_name);
        std::cout << ">>> Field: " << std::quoted(sec_name) << "\n\t";
        for(const auto& field_name : fields)
            std::cout << std::quoted(field_name) << " ";
        std::cout << '\n';
    }


    // Try to get protocol version.
    auto version_num = reader.get_int("protocol","version");
    if(not reader.parsing_ok()){
        std::cout << ">>> Error while retrieving \"protocol\" field from section \"version\"." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        std::cout << "Protocol version is " << version_num << '\n';
    }

    // Try to get pi value.
    auto pi_value = reader.get_real("user","pi");
    if(not reader.parsing_ok()){
        std::cout << ">>> Error while retrieving \"pi\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        std::cout << "Protocol version is " << pi_value << '\n';
    }

    // Try to get pi value.
    auto val= reader.get_real("user","val");
    if(not reader.parsing_ok()){
        std::cout << ">>> Error while retrieving \"val\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        std::cout << "Protocol version is " << val << '\n';
    }

    // Try to get user name
    auto user_name = reader.get_str("user","name", "unknow rr");
    if(not reader.parsing_ok()){
        std::cout << ">>> Error while retrieving \"name\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    }
    std::cout << "User.name is " << user_name << '\n';

    // Try to get user current active status.
    auto user_status = reader.get_bool("user","active");
    if(not reader.parsing_ok()){
        std::cout << ">>> Error while retrieving \"active\" field." << '\n';
        std::cout << "    Msg = " << std::quoted(reader.parser_error_msg()) << '\n';
    } else {
        std::cout << "User.active status name is " << std::boolalpha << user_status << '\n';
    }

    std::cout << "\n>>> Pretty print:" << '\n';
    std::cout << reader.pretty_print() << '\n';

    return 0;
}
