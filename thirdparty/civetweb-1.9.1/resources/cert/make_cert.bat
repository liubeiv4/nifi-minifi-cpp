del server.*

c:\OpenSSL-Win32\bin\openssl.exe genrsa -des3 -out server.key 4096

c:\OpenSSL-Win32\bin\openssl.exe req -sha256 -new -key server.key -out server.csr -utf8

copy server.key server.key.orig

c:\OpenSSL-Win32\bin\openssl.exe rsa -in server.key.orig -out server.key

echo [ v3_ca ] > server.ext.txt
echo [ req ] >> server.ext.txt
echo req_extensions = my_extensions >> server.ext.txt
echo [ my_extensions ] >> server.ext.txt
echo extendedKeyUsage=serverAuth >> server.ext.txt
echo crlDistributionPoints=URI:http://localhost/crl.pem >> server.ext.txt

c:\OpenSSL-Win32\bin\openssl.exe x509 -req -days 365 -extensions v3_ca -extfile server.ext.txt -in server.csr -signkey server.key -out server.crt

copy server.crt server.pem

type server.key >> server.pem
