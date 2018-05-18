#include <stdio.h>
#include <json-c/json.h>
#include <string.h>

int main(int argc, char **argv)
{
    json_object  *temperatureobj, *windobj, *windspeedobj, *winddirecobj,*cloudsobj, *visibilityobj, *precipitationobj, *cityobj, *humidityobj, *pressureobj, *weatherobj, *lastupdateobj,*openweatherobj, *coordobj;
    json_object *dobj,*darray, *dval;

    int arraylen, i;

    //    double lon, lat, temp, temp_min, temp_max, speed, message;
    //    int weatherid, pressure, humidity, deg, all, rain, sysid, type, cityid, code,dt;
    int cityid, humidity, pressure, winddirection, clouds, visibility, weathernumber;

    double lon, lat, temp, temp_min, temp_max, windspeed;
    //json_object  *main, *description, *icon, *base, *country, *name, *sunrise, *sunset;
    json_object *cityname, *country, *sunrise, *sunset, *tempunit, *humidityunit, *pressureunit, *windspeedname,*winddirectioncode, *winddirectionname, *cloudsname, *precipitation, *weathervalue, *weathericon, *lastupdate;

    FILE *fp1;
    char weatherdata[1024];
    fp1 =fopen("weatherdata.txt","rt");

    if(fp1==NULL){
	printf("파일 읽기  실패\n");
	return 0;
    }

    while(!feof(fp1))
    {
	fgets(weatherdata, 1024, fp1);
    }

    printf("weatherobj.to_string()=%s",weatherdata);


    openweatherobj = json_tokener_parse(weatherdata);
    cityobj = json_object_object_get(openweatherobj, "city");
    temperatureobj = json_object_object_get(openweatherobj, "temperature");
    humidityobj = json_object_object_get(openweatherobj, "humidity");
    pressureobj = json_object_object_get(openweatherobj, "pressure");
    windobj = json_object_object_get(openweatherobj, "wind");
    cloudsobj = json_object_object_get(openweatherobj, "clouds");
    visibilityobj = json_object_object_get(openweatherobj, "visibility");
    precipitationobj = json_object_object_get(openweatherobj, "precipitation");
    weatherobj = json_object_object_get(openweatherobj, "weather");
    lastupdateobj = json_object_object_get(openweatherobj, "lastupdate");

    //city영역
    dval = json_object_object_get(cityobj, "id");
    cityid =json_object_get_int(dval);
    printf("city id: %d\n", cityid);

    cityname = json_object_object_get(cityobj, "name");
    printf("city name: %s\n",json_object_get_string(cityname));

    coordobj = json_object_object_get(cityobj, "coord");
    //city coord
    dval = json_object_object_get(coordobj, "lon");
    lon =json_object_get_double(dval);
    printf("lon: %f\n", lon);

    dval = json_object_object_get(coordobj, "lat");
    lat =json_object_get_double(dval);
    printf("lat: %f\n",lat);

    country = json_object_object_get(cityobj, "country");
    printf("country: %s\n",json_object_get_string(country));

    sunrise = json_object_object_get(cityobj, "sunrise");
    printf("sunrise: %s\n",json_object_get_string(sunrise));

    sunset = json_object_object_get(cityobj, "sunset");
    printf("sunset: %s\n",json_object_get_string(sunset));

    //temp 영역
    dval = json_object_object_get(temperatureobj, "value");
    temp =json_object_get_double(dval);
    printf("temperature: %f\n", temp);

    dval = json_object_object_get(temperatureobj, "min");
    temp_min =json_object_get_double(dval);
    printf("temperature min: %f\n", temp_min);

    dval = json_object_object_get(temperatureobj, "max");
    temp_max =json_object_get_double(dval);
    printf("temperature max: %f\n", temp_max);

    tempunit = json_object_object_get(temperatureobj, "unit");
    printf("temperature unit: %s\n",json_object_get_string(tempunit));

    //humidity
    dval = json_object_object_get(humidityobj, "value");
    humidity =json_object_get_int(dval);
    printf("humidity: %d\n",humidity );

    humidityunit = json_object_object_get(humidityobj, "unit");
    printf("humidity unit: %s\n",json_object_get_string(humidityunit));

    //pressure
    dval = json_object_object_get(pressureobj, "value");
    pressure =json_object_get_int(dval);
    printf("pressure: %d\n",pressure);

    pressureunit = json_object_object_get(pressureobj, "unit");
    printf("pressure unit: %s\n",json_object_get_string(pressureunit));

    //wind
    windspeedobj=json_object_object_get(windobj, "speed");
    winddirecobj=json_object_object_get(windobj, "direction");

    //wind speed
    dval = json_object_object_get(windspeedobj, "value");
    windspeed =json_object_get_double(dval);
    printf("wind speed: %f\n",windspeed);

    windspeedname = json_object_object_get(windspeedobj, "name");
    printf("windspeed name: %s\n",json_object_get_string(windspeedname));

    //wind direction
    dval = json_object_object_get(winddirecobj, "value");
    winddirection =json_object_get_int(dval);
    printf("wind direction: %d\n",winddirection);

    winddirectioncode = json_object_object_get(winddirecobj, "code");
    printf("winddirection code: %s\n",json_object_get_string(winddirectioncode));

    winddirectionname = json_object_object_get(winddirecobj, "name");
    printf("winddirection name: %s\n",json_object_get_string(winddirectionname));

    //clouds
    dval = json_object_object_get(cloudsobj, "value");
    clouds =json_object_get_int(dval);
    printf("clouds: %d\n",clouds);

    cloudsname = json_object_object_get(cloudsobj, "name");
    printf("clouds name: %s\n",json_object_get_string(cloudsname));

    //visibility
    dval = json_object_object_get(visibilityobj, "value");
    visibility =json_object_get_int(dval);
    printf("visibility: %d\n", visibility);

    //precipitation
    precipitation = json_object_object_get(precipitationobj, "mode");
    printf("precipitation mode: %s\n",json_object_get_string(precipitation));

    //weather
    dval = json_object_object_get(weatherobj, "number");
    weathernumber =json_object_get_int(dval);
    printf("weather number: %d\n",weathernumber);

    weathervalue = json_object_object_get(weatherobj, "value");
    printf("weather value: %s\n",json_object_get_string(weathervalue));

    weathericon= json_object_object_get(weatherobj, "icon");
    printf("weather icon: %s\n",json_object_get_string(weathericon));

    //lastupdate

    lastupdate= json_object_object_get(lastupdateobj, "value");
    printf("lastupdate: %s\n",json_object_get_string(lastupdate));


    //datapoint generate

    json_object *myobj, *headerobj, *dataobj, *schemaobj, *effectimeobj, *bodyobj, *tempobj, *temp_maxobj, *temp_minobj, *humidity1obj, *pressure1obj, *sunrise1obj, *sunset1obj;

    myobj = json_object_new_object();
    headerobj = json_object_new_object();
    dataobj   = json_object_new_object();
    schemaobj   = json_object_new_object();
    effectimeobj   = json_object_new_object();
    bodyobj   = json_object_new_object();
    tempobj   = json_object_new_object();
    temp_maxobj   = json_object_new_object();
    temp_minobj =  json_object_new_object();
    humidity1obj =  json_object_new_object();
    pressure1obj =  json_object_new_object();
    sunset1obj =  json_object_new_object();
    sunrise1obj =  json_object_new_object();

    //header 영역
    json_object_object_add(headerobj, "id", json_object_new_string("ec4bf973-ea36-49f3-9aaa-69c18c9c7d03"));
    json_object_object_add(headerobj, "creation_date_time", json_object_new_string(json_object_get_string(lastupdate)));
    json_object_object_add(myobj, "header", headerobj);

    // data { ..., nameInfo { ..., } phoneNumber [ ..., ] } 영역 
    json_object_object_add(dataobj, "source_name", json_object_new_string("weather-generator"));
    json_object_object_add(dataobj, "source_creation_date_time", json_object_new_string(json_object_get_string(lastupdate)));

    json_object_object_add(headerobj, "acquisition_provenance", dataobj);
    json_object_object_add(headerobj, "user_id", json_object_new_int(cityid));

    json_object_object_add(schemaobj, "namespace", json_object_new_string("omh"));
    json_object_object_add(schemaobj, "name", json_object_new_string("weather"));
    json_object_object_add(schemaobj, "version", json_object_new_string("1.0"));

    json_object_object_add(headerobj, "schema_id", schemaobj);

    json_object_object_add(effectimeobj, "date_time", json_object_new_string(json_object_get_string(lastupdate)));

    json_object_object_add(bodyobj, "effective_time_frame", effectimeobj);

    json_object_object_add(tempobj, "unit", json_object_new_string(json_object_get_string(tempunit)));
    json_object_object_add(tempobj, "value", json_object_new_double(temp));
    json_object_object_add(bodyobj, "temp", tempobj);

    json_object_object_add(temp_minobj, "unit", json_object_new_string(json_object_get_string(tempunit)));
    json_object_object_add(temp_minobj, "value", json_object_new_double(temp_min));
    json_object_object_add(bodyobj, "temp_min", temp_minobj);

    json_object_object_add(temp_maxobj, "unit", json_object_new_string(json_object_get_string(tempunit)));
    json_object_object_add(temp_maxobj, "value", json_object_new_double(temp_max));
    json_object_object_add(bodyobj, "temp_max", temp_maxobj);

    json_object_object_add(humidity1obj, "unit", json_object_new_string(json_object_get_string(humidityunit)));
    json_object_object_add(humidity1obj, "value", json_object_new_int(humidity));
    json_object_object_add(bodyobj, "humidity", humidity1obj);

    json_object_object_add(pressure1obj, "unit", json_object_new_string(json_object_get_string(pressureunit)));
    json_object_object_add(pressure1obj, "value", json_object_new_int(pressure));
    json_object_object_add(bodyobj, "pressure", pressure1obj);

    json_object_object_add(sunrise1obj, "time", json_object_new_string(json_object_get_string(sunrise)));
    json_object_object_add(bodyobj, "sunrise", sunrise1obj);

    json_object_object_add(sunset1obj, "time", json_object_new_string(json_object_get_string(sunset)));
    json_object_object_add(bodyobj, "sunset", sunset1obj);

    json_object_object_add(myobj, "body", bodyobj);

    printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));
    fclose(fp1);
    return 0;
}
