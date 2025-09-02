divert(-1)
    define(MX_PUBLICKEY_MODE,            0x00000000)
    define(MX_PRIVATEKEY_MODE,           0x00010000)

    define(MX_RSA_ENCRYPT,               0x00000000)
    define(MX_RSA_DECRYPT,               0x00001000)

    define(MX_RSA_KEY_AS_PARAM,          0x00000000)   
    define(MX_RSA_KEY_AS_COMPONENT_FILE, 0x00000100)    
    define(MX_RSA_KEY_AS_PEM_FILE,       0x00000200)

    define(MX_RSA_PADDING_PKCS11,        0x00000001)
    define(MX_RSA_PADDING_SSLV23,        0x00000002)
    define(MX_RSA_PADDING_PKCS1_OAEP,    0x00000003)
    define(MX_RSA_PADDING_X931,          0x00000004)
    define(MX_RSA_PADDING_PKCS1_PSS,     0x00000005)
    define(MX_RSA_PADDING_NO_PADDING,    0x00000000)
divert(0)