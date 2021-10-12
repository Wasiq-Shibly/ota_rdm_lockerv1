void database()
{


  {

    if (WiFi.status() == WL_CONNECTED) {
      if (cnn == false)
      {
        ipadd = "D12";
        cnn = true;
      }
      WiFiClient client;
      HTTPClient http;
      http.useHTTP10(true);
   http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "card_number=";
      httpRequestData += data;
      httpRequestData += "&device=";
      httpRequestData += ipadd; 
      http.addHeader("authorization", "api_pi_12345678!@#$%^&*");
      int httpResponseCode = http.POST(httpRequestData);
      if (httpResponseCode == 200)
      {


        DynamicJsonDocument DeSerial(2048);
        deserializeJson(DeSerial, http.getStream());
        const char* tmp = DeSerial["name"];
        const char* image = DeSerial["image"];
        const char* message = DeSerial["message"];
        const char* branch_name = DeSerial["branch_name"];
        const char* branch_id = DeSerial["branch_id"];
        const bool member_status = DeSerial["member_status"];
        const char* room = DeSerial["room"];
        const size_t CAPACITY = JSON_ARRAY_SIZE(7);
        Serial.println("___________");
        Serial.println(tmp);
        Serial.println(image);
        Serial.println(message);
        Serial.println(branch_name);
        Serial.println(branch_id);
        Serial.println(member_status);
        Serial.println(room);
        Serial.println("___________");
      
        if (member_status) {
          Serial.println("if");
          digitalWrite(Buzzer, HIGH);
          digitalWrite(Lock, LOW);
          delay(100);
          digitalWrite(Buzzer, LOW);

          digitalWrite(GLED, LOW);
          digitalWrite(BLED, HIGH);
          digitalWrite(RLED, HIGH);
          Serial.println("OK");
          delay(3000);
          digitalWrite(Lock, HIGH);
          digitalWrite(GLED, HIGH);
          digitalWrite(BLED, LOW);
          digitalWrite(RLED, HIGH);
        } else {

          Serial.println("else");
          digitalWrite(Buzzer, HIGH);
          digitalWrite(GLED, HIGH);
          digitalWrite(BLED, HIGH);
          digitalWrite(RLED, HIGH);
          delay(100);

          digitalWrite(Buzzer, LOW);
          digitalWrite(GLED, HIGH);
          digitalWrite(BLED, LOW);
          digitalWrite(RLED, HIGH);
          delay(100);

          digitalWrite(Buzzer, HIGH);
          delay(100);
          digitalWrite(Buzzer, LOW);
          delay(100);
          digitalWrite(Buzzer, HIGH);
          delay(100);
          digitalWrite(Buzzer, LOW);
          digitalWrite(GLED, HIGH);
          digitalWrite(BLED, LOW);
          digitalWrite(RLED, HIGH);
        }
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("Body Side: ");
//        Serial.println(payload);
        String status = "";

      }


      else
      {

        Serial.println("Your are not registered");

        digitalWrite(Lock, HIGH);
        digitalWrite(Buzzer, HIGH);

        digitalWrite(GLED, HIGH);
        digitalWrite(BLED, HIGH);
        digitalWrite(RLED, LOW);



        delay(1000);


        digitalWrite(GLED, HIGH);
        digitalWrite(BLED, HIGH);
        digitalWrite(RLED, HIGH);



        delay(100);



        digitalWrite(GLED, HIGH);
        digitalWrite(BLED, HIGH);
        digitalWrite(RLED, LOW);



        delay(100);

        digitalWrite(GLED, HIGH);
        digitalWrite(BLED, LOW);
        digitalWrite(RLED, HIGH);

      }

      digitalWrite(Buzzer, LOW);
      // Free resources
      http.end();
    }
    else {
      cnn = false;
      Serial.println("WiFi Disconnected");

      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, HIGH);
      digitalWrite(RLED, LOW);
    }

  }




}
