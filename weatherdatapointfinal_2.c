#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include <time.h>

char* timeToString(struct tm *t);

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

    FILE *fp1, *weatherdatapoint, *uuid, *hostid;
    char weatherdata[1024];
    struct tm *t;
    time_t timer;

    char uuid1[1024], hostid1[1024];

    fp1 =fopen("weatherdata.txt","r");
    weatherdatapoint =fopen("weatherdatapoint.txt","w+");

    if(fp1==NULL){
	printf(" weatherdata.txt 열기  실패\n");
	return 0;
    } 
    uuid =fopen("uuid.txt","w+");
    if(uuid==NULL){
	printf("uuid.txt 열기  실패\n");
	return 0;
    }
    hostid =fopen("hostid.txt","w+");
    if(hostid==NULL){
	printf("hostid.txt 열기  실패\n");
	return 0;
    }



    while(fgets(weatherdata, 1024, fp1) !=NULL)
    {
	puts(weatherdata);

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer);

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
	//	printf("city id: %d\n", cityid);

	cityname = json_object_object_get(cityobj, "name");
	//	printf("city name: %s\n",json_object_get_string(cityname));

	coordobj = json_object_object_get(cityobj, "coord");
	//city coord
	dval = json_object_object_get(coordobj, "lon");
	lon =json_object_get_double(dval);
	//	printf("lon: %f\n", lon);

	dval = json_object_object_get(coordobj, "lat");
	lat =json_object_get_double(dval);
	//	printf("lat: %f\n",lat);

	country = json_object_object_get(cityobj, "country");
	//	printf("country: %s\n",json_object_get_string(country));

	sunrise = json_object_object_get(cityobj, "sunrise");
	//	printf("sunrise: %s\n",json_object_get_string(sunrise));

	sunset = json_object_object_get(cityobj, "sunset");
	//	printf("sunset: %s\n",json_object_get_string(sunset));

	//temp 영역
	dval = json_object_object_get(temperatureobj, "value");
	temp =json_object_get_double(dval);
	//	printf("temperature: %f\n", temp);

	dval = json_object_object_get(temperatureobj, "min");
	temp_min =json_object_get_double(dval);
	//	printf("temperature min: %f\n", temp_min);

	dval = json_object_object_get(temperatureobj, "max");
	temp_max =json_object_get_double(dval);
	//	printf("temperature max: %f\n", temp_max);

	tempunit = json_object_object_get(temperatureobj, "unit");
	//	printf("temperature unit: %s\n",json_object_get_string(tempunit));

	//humidity
	dval = json_object_object_get(humidityobj, "value");
	humidity =json_object_get_int(dval);
	//	printf("humidity: %d\n",humidity );

	humidityunit = json_object_object_get(humidityobj, "unit");
	//	printf("humidity unit: %s\n",json_object_get_string(humidityunit));

	//pressure
	dval = json_object_object_get(pressureobj, "value");
	pressure =json_object_get_int(dval);
	//	printf("pressure: %d\n",pressure);

	pressureunit = json_object_object_get(pressureobj, "unit");
	//	printf("pressure unit: %s\n",json_object_get_string(pressureunit));

	//wind
	windspeedobj=json_object_object_get(windobj, "speed");
	winddirecobj=json_object_object_get(windobj, "direction");

	//wind speed
	dval = json_object_object_get(windspeedobj, "value");
	windspeed =json_object_get_double(dval);
	//	printf("wind speed: %f\n",windspeed);

	windspeedname = json_object_object_get(windspeedobj, "name");
	//	printf("windspeed name: %s\n",json_object_get_string(windspeedname));

	//wind direction
	dval = json_object_object_get(winddirecobj, "value");
	winddirection =json_object_get_int(dval);
	//	printf("wind direction: %d\n",winddirection);

	winddirectioncode = json_object_object_get(winddirecobj, "code");
	//	printf("winddirection code: %s\n",json_object_get_string(winddirectioncode));

	winddirectionname = json_object_object_get(winddirecobj, "name");
	//	printf("winddirection name: %s\n",json_object_get_string(winddirectionname));

	//clouds
	dval = json_object_object_get(cloudsobj, "value");
	clouds =json_object_get_int(dval);
	//	printf("clouds: %d\n",clouds);

	cloudsname = json_object_object_get(cloudsobj, "name");
	//	printf("clouds name: %s\n",json_object_get_string(cloudsname));

	//visibility
	dval = json_object_object_get(visibilityobj, "value");
	visibility =json_object_get_int(dval);
	//	printf("visibility: %d\n", visibility);

	//precipitation
	precipitation = json_object_object_get(precipitationobj, "mode");
	//	printf("precipitation mode: %s\n",json_object_get_string(precipitation));

	//weather
	dval = json_object_object_get(weatherobj, "number");
	weathernumber =json_object_get_int(dval);
	//	printf("weather number: %d\n",weathernumber);

	weathervalue = json_object_object_get(weatherobj, "value");
	//	printf("weather value: %s\n",json_object_get_string(weathervalue));

	weathericon= json_object_object_get(weatherobj, "icon");
	//	printf("weather icon: %s\n",json_object_get_string(weathericon));

	//lastupdate

	lastupdate= json_object_object_get(lastupdateobj, "value");
	//	printf("lastupdate: %s\n",json_object_get_string(lastupdate));


	//datapoint generate

	json_object *myobj, *headerobj, *dataobj, *schemaobj, *effectimeobj, *bodyobj, *tempobj, *temperature1obj, *temp_maxobj, *temp_minobj, *humidity1obj, *pressure1obj, *sunrise1obj, *sunset1obj, *wind1obj, *windspeed1obj, *winddirec1obj, *clouds1obj, *visibility1obj, *precipitation1obj, *weather1obj, *city1obj, *coord1obj;

	myobj = json_object_new_object();
	headerobj = json_object_new_object();
	dataobj   = json_object_new_object();
	schemaobj   = json_object_new_object();
	effectimeobj   = json_object_new_object();
	bodyobj   = json_object_new_object();
	tempobj   = json_object_new_object();
	temperature1obj   = json_object_new_object();
	temp_maxobj   = json_object_new_object();
	temp_minobj =  json_object_new_object();
	humidity1obj =  json_object_new_object();
	pressure1obj =  json_object_new_object();
	sunset1obj =  json_object_new_object();
	sunrise1obj =  json_object_new_object();
	wind1obj =  json_object_new_object();
	windspeed1obj =  json_object_new_object();
	winddirec1obj =  json_object_new_object();
	clouds1obj =  json_object_new_object();
	visibility1obj =  json_object_new_object();
	precipitation1obj =  json_object_new_object();
	weather1obj =  json_object_new_object();
	city1obj =  json_object_new_object();
	coord1obj =  json_object_new_object();

	system("uuid>>uuid.txt");
	fscanf(uuid,"%s",uuid1);
	//header 영역
	json_object_object_add(headerobj, "id", json_object_new_string(uuid1));
	json_object_object_add(headerobj, "creation_date_time", json_object_new_string(timeToString(t)));
	json_object_object_add(myobj, "header", headerobj);

	// data { ..., nameInfo { ..., } phoneNumber [ ..., ] } 영역 
	json_object_object_add(dataobj, "source_name", json_object_new_string("weather-generator"));
	json_object_object_add(dataobj, "source_creation_date_time", json_object_new_string(json_object_get_string(lastupdate)));

	json_object_object_add(headerobj, "acquisition_provenance", dataobj);

	system("hostid>>hostid.txt");
	fscanf(hostid,"%s",hostid1);
	json_object_object_add(headerobj, "user_id", json_object_new_string(hostid1));

	json_object_object_add(schemaobj, "namespace", json_object_new_string("omh"));
	json_object_object_add(schemaobj, "name", json_object_new_string("weather"));
	json_object_object_add(schemaobj, "version", json_object_new_string("1.0"));

	json_object_object_add(headerobj, "schema_id",schemaobj );

	json_object_object_add(effectimeobj, "date_time", json_object_new_string(json_object_get_string(lastupdate)));

	json_object_object_add(bodyobj, "effective_time_frame", effectimeobj);

	//city 
	printf("test1\n");
	json_object_object_add(city1obj, "id", json_object_new_int(cityid));
	json_object_object_add(city1obj, "name",  json_object_new_string(json_object_get_string(cityname)));
	printf("test2\n");
	json_object_object_add(coord1obj, "lon", json_object_new_double(lon));
	json_object_object_add(coord1obj, "lat", json_object_new_double(lat));
	json_object_object_add(city1obj, "coord", coord1obj);
	printf("test3\n");
	json_object_object_add(city1obj, "country",  json_object_new_string(json_object_get_string(country)));
	json_object_object_add(bodyobj, "city", city1obj);

	//suntime
	json_object_object_add(sunrise1obj, "time", json_object_new_string(json_object_get_string(sunrise)));
	json_object_object_add(bodyobj, "sunrise", sunrise1obj);
	json_object_object_add(sunset1obj, "time", json_object_new_string(json_object_get_string(sunset)));
	json_object_object_add(bodyobj, "sunset", sunset1obj);

	//temperature
	json_object_object_add(temperature1obj, "value", json_object_new_double(temp));
	json_object_object_add(temperature1obj, "min", json_object_new_double(temp_min));
	json_object_object_add(temperature1obj, "max", json_object_new_double(temp_max));
	json_object_object_add(temperature1obj, "unit", json_object_new_string(json_object_get_string(tempunit)));
	json_object_object_add(bodyobj, "temperature", temperature1obj);

	//humidity
	json_object_object_add(humidity1obj, "unit", json_object_new_string(json_object_get_string(humidityunit)));
	json_object_object_add(humidity1obj, "value", json_object_new_int(humidity));
	json_object_object_add(bodyobj, "humidity", humidity1obj);

	//pressure
	json_object_object_add(pressure1obj, "unit", json_object_new_string(json_object_get_string(pressureunit)));
	json_object_object_add(pressure1obj, "value", json_object_new_int(pressure));
	json_object_object_add(bodyobj, "pressure", pressure1obj);

	//windspeed
	json_object_object_add(windspeed1obj, "value", json_object_new_double(windspeed));
	json_object_object_add(windspeed1obj, "name", json_object_new_string(json_object_get_string(windspeedname)));
	json_object_object_add(wind1obj, "speed", windspeed1obj);

	//winddirection
	json_object_object_add(winddirec1obj, "value", json_object_new_int(winddirection));
	json_object_object_add(winddirec1obj, "code", json_object_new_string(json_object_get_string(winddirectioncode)));
	json_object_object_add(winddirec1obj, "name", json_object_new_string(json_object_get_string(winddirectionname)));
	json_object_object_add(wind1obj, "direction", winddirec1obj);
	json_object_object_add(bodyobj, "wind", wind1obj);

	//clouds
	json_object_object_add(clouds1obj, "value", json_object_new_int(clouds));
	json_object_object_add(clouds1obj, "name", json_object_new_string(json_object_get_string(cloudsname)));
	json_object_object_add(bodyobj, "clouds", clouds1obj);

	//visibility
	json_object_object_add(visibility1obj, "value", json_object_new_int(visibility));
	json_object_object_add(bodyobj, "visibility", visibility1obj);

	//precipitation
	json_object_object_add(precipitation1obj, "name", json_object_new_string(json_object_get_string(precipitation)));
	json_object_object_add(bodyobj, "precipitation", precipitation1obj);
	//weather
	json_object_object_add(weather1obj, "number", json_object_new_int(weathernumber));
	json_object_object_add(weather1obj, "value", json_object_new_string(json_object_get_string(weathervalue)));
	json_object_object_add(weather1obj, "icon", json_object_new_string(json_object_get_string(weathericon)));
	json_object_object_add(bodyobj, "weather", weather1obj);



	json_object_object_add(myobj, "body", bodyobj);

	printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));
	fprintf(weatherdatapoint, "%s\n", json_object_to_json_string(myobj));
    }
    fclose(fp1);
    fclose(weatherdatapoint);
    return 0;
}

char* timeToString(struct tm *t) {
    static char s[20];

    sprintf(s, "%04d-%02d-%02dT%02d:%02d:%02dZ",t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return s;
}

