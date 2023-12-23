#include "Env.hpp"
#include "LocationConfig.hpp"
#include "ServerConfig.hpp"
#include "Extractor.hpp"

ConfigInfo*                 Env::_ptr = NULL;
ConfigInfo*                 Env::_prev = NULL;
std::vector<ServerConfig>   Env::_svconfs;

Env::Env() {}

Env::~Env() {
    delete _ptr;
    _ptr = NULL;
}

void    Env::create(TokenType type) {
    if (type == SERVER) {
        delete _ptr;
        _ptr = new ServerConfig();
    }
    else {
        _prev = _ptr;
        _ptr = new LocationConfig();
    }
}

void    Env::put(const std::vector<std::string> &value, const Token &token) {
    Extractor   extract(value, token);

    switch (token.type()) {
        case LISTEN:
            _ptr->set_port_number(extract.port_number());
            break;
        case SERVER_NAME:
            _ptr->set_server_name(extract.server_name());
            break;
        case CLIENT_MAX_BODY_SIZE:
            _ptr->set_client_max_body_size(extract.client_max_body_size());
            break;
        case INDEX:
            _ptr->set_index(extract.index());
            break;
        case ROOT:
            _ptr->set_root(extract.root());
            break;
        case ERROR_PAGE:
            _ptr->set_error_page(extract.error_page());
            break;
        case RETURN:
            _ptr->set_return(extract.return_page());
            break;
        case AUTOINDEX:
            _ptr->set_autoindex(extract.autoindex());
            break;
        case PARAMETER:
            (static_cast<LocationConfig*>(_ptr))->addPath(value);
            break;
        default:
            throw RunTimeException(token, "Invalid Directive.");
    }
}

void    Env::add(TokenType type) {
    if (type == SERVER)
        _svconfs.push_back(*(static_cast<ServerConfig*>(_ptr)));
    else {
        (static_cast<ServerConfig*>(_prev))->addLocation(
                                        *(static_cast<LocationConfig*>(_ptr))
                                        );
        delete _ptr;
        _ptr = _prev;
    }
}

std::vector<ServerConfig>   Env::get() {
    return _svconfs;
}

Env& Env::getInstance() {
    static Env  instance;

    return instance;
}
