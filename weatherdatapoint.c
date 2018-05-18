#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
 #include <time.h>

char* timeToString(struct tm *t);

int main(int argc, char **argv)
{
    json_object *weatherobj, *coordobj, *arrayobj, *weatherdataobj, *mainobj, *windobj, *cloudsobj, *rainobj, *sysobj;
    json_object *dobj,*darray, *dval;

    int arraylen, i;

    double lon, lat, temp, temp_min, temp_max, speed, message;
    int weatherid, pressure, humidity, deg, all, rain, sysid, type, cityid, code,dt;

    json_object  *main, *description, *icon, *base, *country, *name, *sunrise, *sunset;

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



    weatherobj = json_tokener_parse(weatherdata);
    coordobj = json_object_object_get(weatherobj, "coord");
    weatherdataobj = json_object_object_get(weatherobj, "weather");
    mainobj = json_object_object_get(weatherobj, "main");
    windobj = json_object_object_get(weatherobj, "wind");
    cloudsobj = json_object_object_get(weatherobj, "clouds");
    rainobj = json_object_object_get(weatherobj, "rain");
    sysobj = json_object_object_get(weatherobj, "sys");

    //coord영역
    dval = json_object_object_get(coordobj, "lon");
    lon =json_object_get_double(dval);
    printf("lon: %f\n", lon);

    dval = json_object_object_get(coordobj, "lat");
    lat =json_object_get_double(dval);
    printf("lat: %f\n",lat);



    //weather영역

    struct json_object *lArray; 
    lArray=json_object_get(weatherdataobj); 
    darray = json_object_array_get_idx(lArray, 0);
    dval = json_object_object_get(darray, "id");
    weatherid =json_object_get_int(dval);
    printf("weatherid: %d\n", weatherid);

    main = json_object_object_get(darray, "main");
    printf("%s\n",json_object_get_string(main));

    description = json_object_object_get(darray, "description");
    printf("%s\n",json_object_get_string(description));


    icon = json_object_object_get(darray, "icon");
    printf("%s\n",json_object_get_string(icon));

    //base
    base = json_object_object_get(weatherobj, "base");
    printf("%s\n",json_object_get_string(base));

    //main

    dval= json_object_object_get(mainobj, "temp");
    temp =json_object_get_double(dval);
    printf("%f\n",temp);

    dval=json_object_object_get(mainobj, "pressure");
    pressure =json_object_get_int(dval);
    printf("%d\n",pressure);

    dval= json_object_object_get(mainobj, "humidity");
    humidity =json_object_get_int(dval);
    printf("%d\n",humidity);

    dval= json_object_object_get(mainobj, "temp_min");
    temp_min =json_object_get_double(dval);
    printf("%f\n",temp_min);

    dval= json_object_object_get(mainobj, "temp_max");
    temp_max =json_object_get_double(dval);
    printf("%f\n",temp_max);


    //wind
    dval= json_object_object_get(windobj, "speed");
    speed =json_object_get_double(dval);
    printf("%f\n",speed);

    dval= json_object_object_get(windobj, "deg");
    deg =json_object_get_int(dval);
    printf("%d\n",deg);

    //cloud
    dval= json_object_object_get(cloudsobj, "all");
    all =json_object_get_int(dval);
    printf("%d\n",all);

    //rain
    dval= json_object_object_get(rainobj, "3h");
    rain=json_object_get_int(dval);
    printf("%d\n",rain);

    //dt
    dval= json_object_object_get(weatherobj, "dt");
    dt=json_object_get_int(dval);
    printf("%d\n",dt);

    //sys
    dval= json_object_object_get(sysobj, "type");
    type=json_object_get_int(dval);
    printf("%d\n",type);

    dval= json_object_object_get(sysobj, "id");
    sysid=json_object_get_int(dval);
    printf("%d\n",sysid);

    dval= json_object_object_get(sysobj, "message");
    message=json_object_get_double(dval);
    printf("%f\n",message);

    country= json_object_object_get(sysobj, "country");
    printf("%s\n",json_object_get_string(country));

    sunrise= json_object_object_get(sysobj, "sunrise");
    printf("%s\n",json_object_get_string(sunrise));


    sunset= json_object_object_get(sysobj, "sunset");
    printf("%s\n",json_object_get_string(sunset));



    //cityid
    dval= json_object_object_get(weatherobj, "id");
    cityid=json_object_get_int(dval);
    printf("%d\n",cityid);

    //cityname
    name= json_object_object_get(weatherobj, "name");
    printf("%s\n",json_object_get_string(name));

    //internal parameter

    dval= json_object_object_get(weatherobj, "cod");
    code=json_object_get_int(dval);
    printf("%d\n",code);

    //datapoint generate

    json_object *myobj, *headerobj, *dataobj, *schemaobj, *effectimeobj, *bodyobj, *tempobj, *temp_maxobj, *temp_minobj;

    myobj = json_object_new_object();
    headerobj = json_object_new_object();
    dataobj   = json_object_new_object();
    schemaobj   = json_object_new_object();
    effectimeobj   = json_object_new_object();
    bodyobj   = json_object_new_object();
    tempobj   = json_object_new_object();
    temp_maxobj   = json_object_new_object();
    temp_minobj =  json_object_new_object();

    /* header { ..., } 영역 */
    json_object_object_add(headerobj, "id", json_object_new_string("ec4bf973-ea36-49f3-9aaa-69c18c9c7d03"));
    json_object_object_add(headerobj, "creation_date_time", json_object_new_string("2015-01-01T01:48:19Z"));
    json_object_object_add(myobj, "header", headerobj);

    /* data { ..., nameInfo { ..., } phoneNumber [ ..., ] } 영역 */
    json_object_object_add(dataobj, "source_name", json_object_new_string("weather-generator"));
    json_object_object_add(dataobj, "source_creation_date_time", json_object_new_string(json_object_get_string(sunrise)));

    json_object_object_add(headerobj, "acquisition_provenance", dataobj);
    json_object_object_add(headerobj, "user_id", json_object_new_int(cityid));

    json_object_object_add(schemaobj, "namespace", json_object_new_string("omh"));
    json_object_object_add(schemaobj, "name", json_object_new_string(json_object_get_string(name)));
    json_object_object_add(schemaobj, "version", json_object_new_string("1.0"));

    json_object_object_add(headerobj, "schema_id", schemaobj);

    json_object_object_add(effectimeobj, "date_time", json_object_new_int(dt));

    json_object_object_add(bodyobj, "effective_time_frame", effectimeobj);

    json_object_object_add(tempobj, "unit", json_object_new_string("Kelvin"));
    json_object_object_add(tempobj, "value", json_object_new_double(temp));
    json_object_object_add(bodyobj, "temp", tempobj);

    json_object_object_add(temp_minobj, "unit", json_object_new_string("Kelvin"));
    json_object_object_add(temp_minobj, "value", json_object_new_double(temp_min));
    json_object_object_add(bodyobj, "temp_min", temp_minobj);

    json_object_object_add(temp_maxobj, "unit", json_object_new_string("Kelvin"));
    json_object_object_add(temp_maxobj, "value", json_object_new_double(temp_max));
    json_object_object_add(bodyobj, "temp_max", temp_maxobj);
    json_object_object_add(myobj, "body", bodyobj);

    printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));

    fclose(fp1);
    return 0;
}
