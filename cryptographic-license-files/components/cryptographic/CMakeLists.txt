idf_component_register(
	SRCS 
		"cryptographic_main.cpp"
    	"include/ed25519/verify.c"
    	"include/ed25519/sha512.c"
    	"include/ed25519/ge.c"
    	"include/ed25519/fe.c"
    	"include/ed25519/sc.c"
    	"include/sha256/sha256.c"
    INCLUDE_DIRS 
    	"include"
    	"include/base64"
    	"include/ed25519"
    	"include/json"
    	"include/sha256"
    PRIV_REQUIRES
        mbedtls)

