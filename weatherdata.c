#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv)
{
    json_object *myobj, *headerobj, *arrayobj, *weatherdataobj, *mainobj, *windobj, *cloudsobj, *rainobj, *sysobj;

    FILE *fp;
    fp =fopen("weatherdata.txt","wt");

    if(fp==NULL){
	printf("파일 저장 실패\n");
	return 0;
    }


    myobj = json_object_new_object();

    headerobj = json_object_new_object();
    weatherdataobj   = json_object_new_object();
    mainobj   = json_object_new_object();
    windobj   = json_object_new_object();
    cloudsobj   = json_object_new_object();
    rainobj   = json_object_new_object();
    sysobj   = json_object_new_object();


    //coord
    json_object_object_add(headerobj, "lon", json_object_new_double(145.77));
    json_object_object_add(headerobj, "lat", json_object_new_double(-16.92));
    json_object_object_add(myobj, "coord", headerobj);

    // weather data array type 
    arrayobj = json_object_new_array();
    json_object_object_add(weatherdataobj, "id", json_object_new_int(803));
    json_object_object_add(weatherdataobj, "main", json_object_new_string("Clouds"));
    json_object_object_add(weatherdataobj, "description", json_object_new_string("broken clouds"));
    json_object_object_add(weatherdataobj, "icon", json_object_new_string("04n"));


    //weather
    json_object_array_add(arrayobj,weatherdataobj);
    json_object_object_add(myobj, "weather", arrayobj);

    //base

    json_object_object_add(myobj, "base", json_object_new_string("cmc stations"));


    //main
    json_object_object_add(mainobj, "temp", json_object_new_double(293.25));
    json_object_object_add(mainobj, "pressure", json_object_new_int(1019));
    json_object_object_add(mainobj, "humidity", json_object_new_int(83));
    json_object_object_add(mainobj, "temp_min", json_object_new_double(289.82));
    json_object_object_add(mainobj, "temp_max", json_object_new_double(295.37));

    json_object_object_add(myobj, "main",mainobj);

    //wind
    json_object_object_add(windobj, "speed", json_object_new_double(5.1));
    json_object_object_add(windobj, "deg", json_object_new_int(150));
    json_object_object_add(myobj, "wind", windobj);

    //clouds
    json_object_object_add(cloudsobj, "all", json_object_new_int(75));
    json_object_object_add(myobj, "clouds", cloudsobj);

    //rain
    json_object_object_add(rainobj, "3h", json_object_new_int(3));
    json_object_object_add(myobj, "rain", rainobj);


    //dt
    json_object_object_add(myobj, "dt", json_object_new_int(1435658272));

    // sys
    json_object_object_add(sysobj, "type", json_object_new_int(1));
    json_object_object_add(sysobj, "id", json_object_new_int(8166));
    json_object_object_add(sysobj, "message", json_object_new_double(0.0166));
    json_object_object_add(sysobj, "country", json_object_new_string("AU"));
    json_object_object_add(sysobj, "sunrise", json_object_new_string("2015-06-30T03:46:57"));
    json_object_object_add(sysobj, "sunset", json_object_new_string("2015-06-30T20:21:12"));
    json_object_object_add(myobj, "sys", sysobj);

    //rest
    json_object_object_add(myobj, "id", json_object_new_int(2172797));
    json_object_object_add(myobj, "name", json_object_new_string("Cairns"));
    json_object_object_add(myobj, "cod", json_object_new_int(200));

    printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));

    fprintf(fp, "%s\n",json_object_to_json_string(myobj));
    fclose(fp);

    json_object_put(headerobj);
    json_object_put(weatherdataobj);
    json_object_put(myobj);
    json_object_put(mainobj);
    json_object_put(windobj);
    json_object_put(cloudsobj);
    json_object_put(rainobj);
    json_object_put(sysobj);
    return(0);
}
