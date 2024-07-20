package com.snhu.sslserver;

// imports
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

// AES encryption
import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.util.Base64;
import java.security.SecureRandom;

// SHA Checksum (hash)
import java.security.MessageDigest;

// Cryptographic algorithm errors
import java.security.NoSuchAlgorithmException;


@SpringBootApplication
public class SslServerApplication {

	public static void main(String[] args) {
		SpringApplication.run(SslServerApplication.class, args);
	}

}

@RestController
class SslServerController {
    
    private String bytesToHex(byte[] digest) { // digest = hash byte array
        StringBuilder sb = new StringBuilder();
        for (byte b : digest) {
            sb.append(String.format("%02x", b));
        }
        String hexString = sb.toString();
        return hexString;
    }
    
    // SSL Local Server URL: https://localhost:8443/hash
    @RequestMapping("/hash")
    public String getHash() {
        
        try {
            
            // Generate secure pseudo-random number generator for AES
            SecureRandom secureRandom = new SecureRandom();

            // Generate AES key for string encryption
            KeyGenerator keyGen = KeyGenerator.getInstance("AES");
            keyGen.init(256, secureRandom); // 256-bit key
            SecretKey secretKey = keyGen.generateKey();

            // Cipher initialization with AES cipher instance
            Cipher cipher = Cipher.getInstance("AES");
            cipher.init(Cipher.ENCRYPT_MODE, secretKey); // set to ENCRYPT_MODE and pass secretKey

            // Encrypt byte array form of data (text string)
            String data = "Matthew Pool";
            byte[] cipherBytes = cipher.doFinal(data.getBytes()); // doFinal() performs final encryption operation
                                                                        // getBytes() converts data string to byte array
            // Convert encrypted byte array to Base64 (test-based strings)
            String cipherText = Base64.getEncoder().encodeToString(cipherBytes);
                      
            // Create MessageDigest instance
            MessageDigest md;
            
            // Initialize object with SHA-256
            md = MessageDigest.getInstance("SHA-256");
            
            // Pass data (cipherText) to MessageDigest object
            md.update(cipherText.getBytes());
            
            // MessageDigest.digest() String to calculate hash value (byte array)
            byte[] digest = md.digest(); // digest is the checksum
            
            // Convert checksum byte array to hex string
            String hexString = bytesToHex(digest);
            
            // return formatted text to web browser
            return "<p>data: " + data + "<p>CheckSum Value: " + hexString; // data = FirstName LastName
                        
        } catch (NoSuchAlgorithmException e) {
            /*e.printStackTrace();*/
            return "Algorithm not supported!";
        
        } catch (Exception e) { 
            /*e.printStackTrace();*/
            return "Error Occurred!";
        }

    }

}
