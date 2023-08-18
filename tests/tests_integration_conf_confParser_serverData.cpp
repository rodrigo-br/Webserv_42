#include "tests.hpp"

/*
    valid_01.conf:
server {
    listen 8000
    root wwwroot

    location / {
        http_methods 4
        index index.html
    }

    location /api {
        index api.html
    }

    location /api/upload {
        http_methods 7
        index upload.html
    }

    location /images {
        index images.html
    }

    location /images/random {
        directory_listing on
        index index.html
    }
}

server {
    listen 4000
    root wwwroot

    location / {
        http_methods 4
        index index.html
    }

    location /api/upload {
        http_methods 4
        index upload.html
    }
}

*/

TEST_CASE("Testa se configurações do conf/default.conf são passadas corretamente aos ServersData")
{
    Conf conf = Conf(new ConfParser("./tests/confs/validos/valid_01.conf"));

    REQUIRE(conf.getServersData()[8000].getRoot() == "wwwroot");
    REQUIRE(conf.getServersData()[8000].getLocation("/cgi-bin") == "index.py");

    conf.deleteConfParser();
}
