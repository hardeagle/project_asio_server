//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef __NET_SSL_CERTIFICATE_H__
#define __NET_SSL_CERTIFICATE_H__

#include <boost/asio/ssl.hpp>
#include <string>

/*
    PLEASE READ

    These root certificates here are included just to make the
    SSL client examples work. They are NOT intended to be
    illustrative of best-practices for performing TLS certificate
    verification.

    A REAL program which needs to verify the authenticity of a
    server IP address resolved from a given DNS name needs to
    consult the operating system specific certificate store
    to validate the chain of signatures, compare the domain name
    properly against the domain name in the certificate, check
    the certificate revocation list, and probably do some other
    things.

    ALL of these operations are entirely outside the scope of
    both Boost.Beast and Boost.Asio.

    See (work in progress):
        https://github.com/djarek/certify

    tl;dr: root_certificates.hpp should not be used in production code
*/

namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>

namespace detail {

inline
void
load_root_certificates(ssl::context& ctx, boost::system::error_code& ec)
{
    std::string const cert =
        /*  This is the DigiCert Global Root CA

            CN = DigiCert High Assurance EV Root CA
            OU = www.digicert.com
            O = DigiCert Inc
            C = US

            Valid to: 10 November 2031
                                
            Serial #:
            08:3B:E0:56:90:42:46:B1:A1:75:6A:C9:59:91:C7:4A

            SHA1 Fingerprint:
            A8:98:5D:3A:65:E5:E5:C4:B2:D7:D6:6D:40:C6:DD:2F:B1:9C:54:36

            SHA256 Fingerprint:
            43:48:A0:E9:44:4C:78:CB:26:5E:05:8D:5E:89:44:B4:D8:4F:96:62:BD:26:DB:25:7F:89:34:A4:43:C7:01:61
        */
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
        "QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\n"
        "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
        "b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\n"
        "9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\n"
        "CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\n"
        "nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\n"
        "43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\n"
        "T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\n"
        "gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\n"
        "BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\n"
        "TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\n"
        "DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\n"
        "hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\n"
        "06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\n"
        "PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\n"
        "YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
        "CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
        "-----END CERTIFICATE-----\n"

        /*  This is the GeoTrust root certificate.
            
            CN = GeoTrust Global CA
            O = GeoTrust Inc.
            C = US
            Valid to: Friday, ‎May ‎20, ‎2022 9:00:00 PM
                                
            Thumbprint(sha1):
            ‎de 28 f4 a4 ff e5 b9 2f a3 c5 03 d1 a3 49 a7 f9 96 2a 82 12
        */
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDaDCCAlCgAwIBAgIJAO8vBu8i8exWMA0GCSqGSIb3DQEBCwUAMEkxCzAJBgNV\n"
        "BAYTAlVTMQswCQYDVQQIDAJDQTEtMCsGA1UEBwwkTG9zIEFuZ2VsZXNPPUJlYXN0\n"
        "Q049d3d3LmV4YW1wbGUuY29tMB4XDTE3MDUwMzE4MzkxMloXDTQ0MDkxODE4Mzkx\n"
        "MlowSTELMAkGA1UEBhMCVVMxCzAJBgNVBAgMAkNBMS0wKwYDVQQHDCRMb3MgQW5n\n"
        "ZWxlc089QmVhc3RDTj13d3cuZXhhbXBsZS5jb20wggEiMA0GCSqGSIb3DQEBAQUA\n"
        "A4IBDwAwggEKAoIBAQDJ7BRKFO8fqmsEXw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcF\n"
        "xqGitbnLIrOgiJpRAPLy5MNcAXE1strVGfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7b\n"
        "Fu8TsCzO6XrxpnVtWk506YZ7ToTa5UjHfBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO\n"
        "9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wWKIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBp\n"
        "yY8anC8u4LPbmgW0/U31PH0rRVfGcBbZsAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrv\n"
        "enu2tOK9Qx6GEzXh3sekZkxcgh+NlIxCNxu//Dk9AgMBAAGjUzBRMB0GA1UdDgQW\n"
        "BBTZh0N9Ne1OD7GBGJYz4PNESHuXezAfBgNVHSMEGDAWgBTZh0N9Ne1OD7GBGJYz\n"
        "4PNESHuXezAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQCmTJVT\n"
        "LH5Cru1vXtzb3N9dyolcVH82xFVwPewArchgq+CEkajOU9bnzCqvhM4CryBb4cUs\n"
        "gqXWp85hAh55uBOqXb2yyESEleMCJEiVTwm/m26FdONvEGptsiCmF5Gxi0YRtn8N\n"
        "V+KhrQaAyLrLdPYI7TrwAOisq2I1cD0mt+xgwuv/654Rl3IhOMx+fKWKJ9qLAiaE\n"
        "fQyshjlPP9mYVxWOxqctUdQ8UnsUKKGEUcVrA08i1OAnVKlPFjKBvk+r7jpsTPcr\n"
        "9pWXTO9JrYMML7d+XRSZA1n3856OqZDX4403+9FnXCvfcLZLLKTBvwwFgEFGpzjK\n"
        "UEVbkhd5qstF6qWK\n"
        "-----END CERTIFICATE-----\n";
        ;
// "-----BEGIN CERTIFICATE-----\n"
// "MIIGDTCCBPWgAwIBAgIQAp4xQ10LNcvYj1zY/F/TojANBgkqhkiG9w0BAQsFADBy\n"
// "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n"
// "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n"
// "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTIxMDYxNTAwMDAwMFoXDTIyMDYxNDIzNTk1\n"
// "OVowFDESMBAGA1UEAxMJZWF5ZXcuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A\n"
// "MIIBCgKCAQEAwW37N3dIRwUR4WRV66A4PHLYxgvJzskWlLF79I/JTlscZDdot5bG\n"
// "PiPW52F8j9r4tz3t/hql62R41o8e9pAsDeUtbtfXEO53aNC1AqMBybG94bUgoOl8\n"
// "RYWmZ3Vvn389NCwNVP1qy5JnPai5jvb04i6cNxHmCYrPmcRx23oMPRYe89XPGUKV\n"
// "js1B6BkkJC62QNaoAK+ceTJ/xKcZyTUAis/4kJ5/hj79BEmWayt1if5ReSbmii4a\n"
// "ZlnFI07oJd8z0/sQalSTRvN/I9k8k8kdM/JuHi+wJEve7RSR5kLYdadiFx0uPnvv\n"
// "iGlGYCbxeiDai1TKwYsUWo+1bPt2Xj0gSwIDAQABo4IC+zCCAvcwHwYDVR0jBBgw\n"
// "FoAUf9OZ86BHDjEAVlYijrfMnt3KAYowHQYDVR0OBBYEFBWzn+pGL4mqIcYjDoCi\n"
// "IMOO5Mk/MCMGA1UdEQQcMBqCCWVheWV3LmNvbYINd3d3LmVheWV3LmNvbTAOBgNV\n"
// "HQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMD4GA1Ud\n"
// "IAQ3MDUwMwYGZ4EMAQIBMCkwJwYIKwYBBQUHAgEWG2h0dHA6Ly93d3cuZGlnaWNl\n"
// "cnQuY29tL0NQUzCBkgYIKwYBBQUHAQEEgYUwgYIwNAYIKwYBBQUHMAGGKGh0dHA6\n"
// "Ly9zdGF0dXNlLmRpZ2l0YWxjZXJ0dmFsaWRhdGlvbi5jb20wSgYIKwYBBQUHMAKG\n"
// "Pmh0dHA6Ly9jYWNlcnRzLmRpZ2l0YWxjZXJ0dmFsaWRhdGlvbi5jb20vVHJ1c3RB\n"
// "c2lhVExTUlNBQ0EuY3J0MAkGA1UdEwQCMAAwggF/BgorBgEEAdZ5AgQCBIIBbwSC\n"
// "AWsBaQB2ACl5vvCeOTkh8FZzn2Old+W+V32cYAr4+U1dJlwlXceEAAABehBALsQA\n"
// "AAQDAEcwRQIhAKZIOBw/ricVSYi4BLtbMMfZQyzLk6mQprBNM3KWFzmzAiAJNFFo\n"
// "kLubFwcJTPA7iDTtR1fczX9pw5lCZV7N5iffmAB2ACJFRQdZVSRWlj+hL/H3bYbg\n"
// "IyZjrcBLf13Gg1xu4g8CAAABehBALt0AAAQDAEcwRQIgJimriRLXkVsX6cMLVSWj\n"
// "dTGE87nB+EGEJqKVbCR2uqkCIQDxMOo68k4iTu90d4/90pooIl4IvYIohzYopb8y\n"
// "5kJsYAB3AFGjsPX9AXmcVm24N3iPDKR6zBsny/eeiEKaDf7UiwXlAAABehBALvsA\n"
// "AAQDAEgwRgIhAIxCyFoFJ2NuLoCCyjdwKaAU9MGz5wdGRxCTOT+ewAMSAiEAuaz/\n"
// "PH/gbFg/ueDIg/GCAl76zlP95r9rtLXngieTIgwwDQYJKoZIhvcNAQELBQADggEB\n"
// "AC9Ni+dKLrq2bXuMQguq8cjPvSR2CDTGXzOt8/SeB0jc9ZOOCfSnuf2Is6uGwEGW\n"
// "E0ZcROmBqWDnb9igvsG4q1WPpw+feBsvjlB5L+14/C3BiMeSxM/VDKfpCYgqIN7v\n"
// "qNAhzhRQi4bR+O7usCPR2mKukno+TUu68rrP3+wk43gpSFmx92tij9xjvcRZEZaz\n"
// "ufKhOaXXvdNgnIqzQMntsQPs/1cbwqeINDyzk8HizDztPHktnmJ2VjpkY67UpIGu\n"
// "MSeAcE7H4+uZDc6z+uAa0mu2lB4ylQ+5VTFQBecL+6WaszTDs4Su2YzN6clSgVzl\n"
// "/+UDlfam+h1jBZjXiKfedoM=\n"
// "-----END CERTIFICATE-----\n"
// "-----BEGIN CERTIFICATE-----\n"
// "MIIErjCCA5agAwIBAgIQBYAmfwbylVM0jhwYWl7uLjANBgkqhkiG9w0BAQsFADBh\n"
// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
// "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
// "QTAeFw0xNzEyMDgxMjI4MjZaFw0yNzEyMDgxMjI4MjZaMHIxCzAJBgNVBAYTAkNO\n"
// "MSUwIwYDVQQKExxUcnVzdEFzaWEgVGVjaG5vbG9naWVzLCBJbmMuMR0wGwYDVQQL\n"
// "ExREb21haW4gVmFsaWRhdGVkIFNTTDEdMBsGA1UEAxMUVHJ1c3RBc2lhIFRMUyBS\n"
// "U0EgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCgWa9X+ph+wAm8\n"
// "Yh1Fk1MjKbQ5QwBOOKVaZR/OfCh+F6f93u7vZHGcUU/lvVGgUQnbzJhR1UV2epJa\n"
// "e+m7cxnXIKdD0/VS9btAgwJszGFvwoqXeaCqFoP71wPmXjjUwLT70+qvX4hdyYfO\n"
// "JcjeTz5QKtg8zQwxaK9x4JT9CoOmoVdVhEBAiD3DwR5fFgOHDwwGxdJWVBvktnoA\n"
// "zjdTLXDdbSVC5jZ0u8oq9BiTDv7jAlsB5F8aZgvSZDOQeFrwaOTbKWSEInEhnchK\n"
// "ZTD1dz6aBlk1xGEI5PZWAnVAba/ofH33ktymaTDsE6xRDnW97pDkimCRak6CEbfe\n"
// "3dXw6OV5AgMBAAGjggFPMIIBSzAdBgNVHQ4EFgQUf9OZ86BHDjEAVlYijrfMnt3K\n"
// "AYowHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQD\n"
// "AgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAG\n"
// "AQH/AgEAMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3Au\n"
// "ZGlnaWNlcnQuY29tMEIGA1UdHwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2lj\n"
// "ZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RDQS5jcmwwTAYDVR0gBEUwQzA3Bglg\n"
// "hkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29t\n"
// "L0NQUzAIBgZngQwBAgEwDQYJKoZIhvcNAQELBQADggEBAK3dVOj5dlv4MzK2i233\n"
// "lDYvyJ3slFY2X2HKTYGte8nbK6i5/fsDImMYihAkp6VaNY/en8WZ5qcrQPVLuJrJ\n"
// "DSXT04NnMeZOQDUoj/NHAmdfCBB/h1bZ5OGK6Sf1h5Yx/5wR4f3TUoPgGlnU7EuP\n"
// "ISLNdMRiDrXntcImDAiRvkh5GJuH4YCVE6XEntqaNIgGkRwxKSgnU3Id3iuFbW9F\n"
// "UQ9Qqtb1GX91AJ7i4153TikGgYCdwYkBURD8gSVe8OAco6IfZOYt/TEwii1Ivi1C\n"
// "qnuUlWpsF1LdQNIdfbW3TSe0BhQa7ifbVIfvPWHYOu3rkg1ZeMo6XRU9B4n5VyJY\n"
// "RmE=\n"
// "-----END CERTIFICATE-----\n";




// "-----BEGIN CERTIFICATE-----\n"
// "MIIGDjCCBPagAwIBAgIQDc7EYMN1wq5Nh8nBe1+tfjANBgkqhkiG9w0BAQsFADBy\n"
// "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n"
// "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n"
// "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTIxMDYxNTAwMDAwMFoXDTIyMDYxNjIzNTk1\n"
// "OVowGDEWMBQGA1UEAxMNd3d3LmVheWV3LmNvbTCCASIwDQYJKoZIhvcNAQEBBQAD\n"
// "ggEPADCCAQoCggEBAL9TN4hgo0UX8mmiBpPlhpTaLo5jtY3CCViWRh8Z/ZszWgZX\n"
// "kgIEFAtw1tosEwRHBQThmj1Ku/HO3zN/6s/A4IuYQvlgaZp9SBftjACM0/LY16y2\n"
// "DN07UhXVqY/QYHQxtE1WB7c0gKLQtFcqF2nOOlT9Q4Pat4RA/zGCgClOoUB0do81\n"
// "nCbTbngV34d/ZX9Q3rF7FPENejAXbPUj5BoGp7mT/BATKj/UIw3lrxkMjfrUZ6q3\n"
// "cOIHtncz9auVWGdjTP5a0DLW1XYTqB9tLYiW6+kfLhXdaNMeCJDNLQCYDE26MYLP\n"
// "iRB7BVt3fUob9EkjD0uDvJjNXGS8rioaLi7Qp+cCAwEAAaOCAvgwggL0MB8GA1Ud\n"
// "IwQYMBaAFH/TmfOgRw4xAFZWIo63zJ7dygGKMB0GA1UdDgQWBBQynLfBwOr8rt/Q\n"
// "PboZJYQynSvDKzAjBgNVHREEHDAagg13d3cuZWF5ZXcuY29tggllYXlldy5jb20w\n"
// "DgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjA+\n"
// "BgNVHSAENzA1MDMGBmeBDAECATApMCcGCCsGAQUFBwIBFhtodHRwOi8vd3d3LmRp\n"
// "Z2ljZXJ0LmNvbS9DUFMwgZIGCCsGAQUFBwEBBIGFMIGCMDQGCCsGAQUFBzABhiho\n"
// "dHRwOi8vc3RhdHVzZS5kaWdpdGFsY2VydHZhbGlkYXRpb24uY29tMEoGCCsGAQUF\n"
// "BzAChj5odHRwOi8vY2FjZXJ0cy5kaWdpdGFsY2VydHZhbGlkYXRpb24uY29tL1Ry\n"
// "dXN0QXNpYVRMU1JTQUNBLmNydDAJBgNVHRMEAjAAMIIBfAYKKwYBBAHWeQIEAgSC\n"
// "AWwEggFoAWYAdQApeb7wnjk5IfBWc59jpXflvld9nGAK+PlNXSZcJV3HhAAAAXoP\n"
// "/ajHAAAEAwBGMEQCID3XekruJIFJn/ruLvn4GH8fE/yyjQNseVW2bXzsaB2vAiAK\n"
// "tUnCJhBrZP5DYmFjCeVO7k+Pd1XiRHMCKSmMa+kI6QB2ACJFRQdZVSRWlj+hL/H3\n"
// "bYbgIyZjrcBLf13Gg1xu4g8CAAABeg/9qPUAAAQDAEcwRQIgZfPIJ07+Jj/C+N7c\n"
// "lC1c+vz48T6Gb8ADsquZ+F6WdoUCIQDt0zLQbl4OelVtfnW7FdTH0i6Ol2w3HuMB\n"
// "kTFejcoVDQB1AFGjsPX9AXmcVm24N3iPDKR6zBsny/eeiEKaDf7UiwXlAAABeg/9\n"
// "qTYAAAQDAEYwRAIgDrMeFrDWJYR7YRR8UBG1CtF5ctTb2oGJRbX8k320VfgCIG/3\n"
// "NYkyZ8gfhPTSbxZecagKVBzBBDQTXVXTC43HM4wrMA0GCSqGSIb3DQEBCwUAA4IB\n"
// "AQCG7NLm/5JlGbuXcUFqsn85Bge3px7Mr7M1x3ADqrRxnntvnAhi2EVXV2jP4Ogq\n"
// "uQUqtgq06xILL/L1gyoy6Nmd2HfwW4Y4sdWeX1IJOr1bgCMHryopqD+dRe058moG\n"
// "eBkJvU6IX4myjSqVkBMURxF5tSvQy5VgJKBcSfg/sSgMeKxDVh4bnP870OQ3TV44\n"
// "NRw0c3fDVZGmoQsJvBp9R1JuCGaS7/lxktjUbYIPfx9ZR8JjI82q0quBt4h3jyCf\n"
// "9fZsTQQRoff/MPaRSSg4a+dGVmdxUACezACZAYa2qdppX8iJx3bzqYAx6XWsnq9S\n"
// "l8MI738OBljYfEzNPEtje+2D\n"
// "-----END CERTIFICATE-----\n"
// "-----BEGIN CERTIFICATE-----\n"
// "MIIErjCCA5agAwIBAgIQBYAmfwbylVM0jhwYWl7uLjANBgkqhkiG9w0BAQsFADBh\n"
// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
// "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
// "QTAeFw0xNzEyMDgxMjI4MjZaFw0yNzEyMDgxMjI4MjZaMHIxCzAJBgNVBAYTAkNO\n"
// "MSUwIwYDVQQKExxUcnVzdEFzaWEgVGVjaG5vbG9naWVzLCBJbmMuMR0wGwYDVQQL\n"
// "ExREb21haW4gVmFsaWRhdGVkIFNTTDEdMBsGA1UEAxMUVHJ1c3RBc2lhIFRMUyBS\n"
// "U0EgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCgWa9X+ph+wAm8\n"
// "Yh1Fk1MjKbQ5QwBOOKVaZR/OfCh+F6f93u7vZHGcUU/lvVGgUQnbzJhR1UV2epJa\n"
// "e+m7cxnXIKdD0/VS9btAgwJszGFvwoqXeaCqFoP71wPmXjjUwLT70+qvX4hdyYfO\n"
// "JcjeTz5QKtg8zQwxaK9x4JT9CoOmoVdVhEBAiD3DwR5fFgOHDwwGxdJWVBvktnoA\n"
// "zjdTLXDdbSVC5jZ0u8oq9BiTDv7jAlsB5F8aZgvSZDOQeFrwaOTbKWSEInEhnchK\n"
// "ZTD1dz6aBlk1xGEI5PZWAnVAba/ofH33ktymaTDsE6xRDnW97pDkimCRak6CEbfe\n"
// "3dXw6OV5AgMBAAGjggFPMIIBSzAdBgNVHQ4EFgQUf9OZ86BHDjEAVlYijrfMnt3K\n"
// "AYowHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQD\n"
// "AgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAG\n"
// "AQH/AgEAMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3Au\n"
// "ZGlnaWNlcnQuY29tMEIGA1UdHwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2lj\n"
// "ZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RDQS5jcmwwTAYDVR0gBEUwQzA3Bglg\n"
// "hkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29t\n"
// "L0NQUzAIBgZngQwBAgEwDQYJKoZIhvcNAQELBQADggEBAK3dVOj5dlv4MzK2i233\n"
// "lDYvyJ3slFY2X2HKTYGte8nbK6i5/fsDImMYihAkp6VaNY/en8WZ5qcrQPVLuJrJ\n"
// "DSXT04NnMeZOQDUoj/NHAmdfCBB/h1bZ5OGK6Sf1h5Yx/5wR4f3TUoPgGlnU7EuP\n"
// "ISLNdMRiDrXntcImDAiRvkh5GJuH4YCVE6XEntqaNIgGkRwxKSgnU3Id3iuFbW9F\n"
// "UQ9Qqtb1GX91AJ7i4153TikGgYCdwYkBURD8gSVe8OAco6IfZOYt/TEwii1Ivi1C\n"
// "qnuUlWpsF1LdQNIdfbW3TSe0BhQa7ifbVIfvPWHYOu3rkg1ZeMo6XRU9B4n5VyJY\n"
// "RmE=\n"
// "-----END CERTIFICATE-----\n";


// "-----BEGIN CERTIFICATE-----\n"
// "MIIGDjCCBPagAwIBAgIQDc7EYMN1wq5Nh8nBe1+tfjANBgkqhkiG9w0BAQsFADBy\n"
// "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n"
// "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n"
// "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTIxMDYxNTAwMDAwMFoXDTIyMDYxNjIzNTk1\n"
// "OVowGDEWMBQGA1UEAxMNd3d3LmVheWV3LmNvbTCCASIwDQYJKoZIhvcNAQEBBQAD\n"
// "ggEPADCCAQoCggEBAL9TN4hgo0UX8mmiBpPlhpTaLo5jtY3CCViWRh8Z/ZszWgZX\n"
// "kgIEFAtw1tosEwRHBQThmj1Ku/HO3zN/6s/A4IuYQvlgaZp9SBftjACM0/LY16y2\n"
// "DN07UhXVqY/QYHQxtE1WB7c0gKLQtFcqF2nOOlT9Q4Pat4RA/zGCgClOoUB0do81\n"
// "nCbTbngV34d/ZX9Q3rF7FPENejAXbPUj5BoGp7mT/BATKj/UIw3lrxkMjfrUZ6q3\n"
// "cOIHtncz9auVWGdjTP5a0DLW1XYTqB9tLYiW6+kfLhXdaNMeCJDNLQCYDE26MYLP\n"
// "iRB7BVt3fUob9EkjD0uDvJjNXGS8rioaLi7Qp+cCAwEAAaOCAvgwggL0MB8GA1Ud\n"
// "IwQYMBaAFH/TmfOgRw4xAFZWIo63zJ7dygGKMB0GA1UdDgQWBBQynLfBwOr8rt/Q\n"
// "PboZJYQynSvDKzAjBgNVHREEHDAagg13d3cuZWF5ZXcuY29tggllYXlldy5jb20w\n"
// "DgYDVR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjA+\n"
// "BgNVHSAENzA1MDMGBmeBDAECATApMCcGCCsGAQUFBwIBFhtodHRwOi8vd3d3LmRp\n"
// "Z2ljZXJ0LmNvbS9DUFMwgZIGCCsGAQUFBwEBBIGFMIGCMDQGCCsGAQUFBzABhiho\n"
// "dHRwOi8vc3RhdHVzZS5kaWdpdGFsY2VydHZhbGlkYXRpb24uY29tMEoGCCsGAQUF\n"
// "BzAChj5odHRwOi8vY2FjZXJ0cy5kaWdpdGFsY2VydHZhbGlkYXRpb24uY29tL1Ry\n"
// "dXN0QXNpYVRMU1JTQUNBLmNydDAJBgNVHRMEAjAAMIIBfAYKKwYBBAHWeQIEAgSC\n"
// "AWwEggFoAWYAdQApeb7wnjk5IfBWc59jpXflvld9nGAK+PlNXSZcJV3HhAAAAXoP\n"
// "/ajHAAAEAwBGMEQCID3XekruJIFJn/ruLvn4GH8fE/yyjQNseVW2bXzsaB2vAiAK\n"
// "tUnCJhBrZP5DYmFjCeVO7k+Pd1XiRHMCKSmMa+kI6QB2ACJFRQdZVSRWlj+hL/H3\n"
// "bYbgIyZjrcBLf13Gg1xu4g8CAAABeg/9qPUAAAQDAEcwRQIgZfPIJ07+Jj/C+N7c\n"
// "lC1c+vz48T6Gb8ADsquZ+F6WdoUCIQDt0zLQbl4OelVtfnW7FdTH0i6Ol2w3HuMB\n"
// "kTFejcoVDQB1AFGjsPX9AXmcVm24N3iPDKR6zBsny/eeiEKaDf7UiwXlAAABeg/9\n"
// "qTYAAAQDAEYwRAIgDrMeFrDWJYR7YRR8UBG1CtF5ctTb2oGJRbX8k320VfgCIG/3\n"
// "NYkyZ8gfhPTSbxZecagKVBzBBDQTXVXTC43HM4wrMA0GCSqGSIb3DQEBCwUAA4IB\n"
// "AQCG7NLm/5JlGbuXcUFqsn85Bge3px7Mr7M1x3ADqrRxnntvnAhi2EVXV2jP4Ogq\n"
// "uQUqtgq06xILL/L1gyoy6Nmd2HfwW4Y4sdWeX1IJOr1bgCMHryopqD+dRe058moG\n"
// "eBkJvU6IX4myjSqVkBMURxF5tSvQy5VgJKBcSfg/sSgMeKxDVh4bnP870OQ3TV44\n"
// "NRw0c3fDVZGmoQsJvBp9R1JuCGaS7/lxktjUbYIPfx9ZR8JjI82q0quBt4h3jyCf\n"
// "9fZsTQQRoff/MPaRSSg4a+dGVmdxUACezACZAYa2qdppX8iJx3bzqYAx6XWsnq9S\n"
// "l8MI738OBljYfEzNPEtje+2D\n"
// "-----END CERTIFICATE-----\n"
// "-----BEGIN CERTIFICATE-----\n"
// "MIIErjCCA5agAwIBAgIQBYAmfwbylVM0jhwYWl7uLjANBgkqhkiG9w0BAQsFADBh\n"
// "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
// "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
// "QTAeFw0xNzEyMDgxMjI4MjZaFw0yNzEyMDgxMjI4MjZaMHIxCzAJBgNVBAYTAkNO\n"
// "MSUwIwYDVQQKExxUcnVzdEFzaWEgVGVjaG5vbG9naWVzLCBJbmMuMR0wGwYDVQQL\n"
// "ExREb21haW4gVmFsaWRhdGVkIFNTTDEdMBsGA1UEAxMUVHJ1c3RBc2lhIFRMUyBS\n"
// "U0EgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCgWa9X+ph+wAm8\n"
// "Yh1Fk1MjKbQ5QwBOOKVaZR/OfCh+F6f93u7vZHGcUU/lvVGgUQnbzJhR1UV2epJa\n"
// "e+m7cxnXIKdD0/VS9btAgwJszGFvwoqXeaCqFoP71wPmXjjUwLT70+qvX4hdyYfO\n"
// "JcjeTz5QKtg8zQwxaK9x4JT9CoOmoVdVhEBAiD3DwR5fFgOHDwwGxdJWVBvktnoA\n"
// "zjdTLXDdbSVC5jZ0u8oq9BiTDv7jAlsB5F8aZgvSZDOQeFrwaOTbKWSEInEhnchK\n"
// "ZTD1dz6aBlk1xGEI5PZWAnVAba/ofH33ktymaTDsE6xRDnW97pDkimCRak6CEbfe\n"
// "3dXw6OV5AgMBAAGjggFPMIIBSzAdBgNVHQ4EFgQUf9OZ86BHDjEAVlYijrfMnt3K\n"
// "AYowHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQD\n"
// "AgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAG\n"
// "AQH/AgEAMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3Au\n"
// "ZGlnaWNlcnQuY29tMEIGA1UdHwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2lj\n"
// "ZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RDQS5jcmwwTAYDVR0gBEUwQzA3Bglg\n"
// "hkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29t\n"
// "L0NQUzAIBgZngQwBAgEwDQYJKoZIhvcNAQELBQADggEBAK3dVOj5dlv4MzK2i233\n"
// "lDYvyJ3slFY2X2HKTYGte8nbK6i5/fsDImMYihAkp6VaNY/en8WZ5qcrQPVLuJrJ\n"
// "DSXT04NnMeZOQDUoj/NHAmdfCBB/h1bZ5OGK6Sf1h5Yx/5wR4f3TUoPgGlnU7EuP\n"
// "ISLNdMRiDrXntcImDAiRvkh5GJuH4YCVE6XEntqaNIgGkRwxKSgnU3Id3iuFbW9F\n"
// "UQ9Qqtb1GX91AJ7i4153TikGgYCdwYkBURD8gSVe8OAco6IfZOYt/TEwii1Ivi1C\n"
// "qnuUlWpsF1LdQNIdfbW3TSe0BhQa7ifbVIfvPWHYOu3rkg1ZeMo6XRU9B4n5VyJY\n"
// "RmE=\n"
// "-----END CERTIFICATE-----\n";



    ctx.add_certificate_authority(
        boost::asio::buffer(cert.data(), cert.size()), ec);
    if(ec)
        return;
}

} // detail

// Load the root certificates into an ssl::context

inline
void
load_root_certificates(ssl::context& ctx, boost::system::error_code& ec)
{
    detail::load_root_certificates(ctx, ec);
}

inline
void
load_root_certificates(ssl::context& ctx)
{
    boost::system::error_code ec;
    detail::load_root_certificates(ctx, ec);
    if(ec)
        throw boost::system::system_error{ec};
}

#endif
