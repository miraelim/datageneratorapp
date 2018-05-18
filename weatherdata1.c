#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv)
{
    json_object *myobj, *headerobj, *arrayobj, *weatherdataobj, *temperatureobj, *windobj, *windspeedobj, *winddirecobj,*cloudsobj, *visibilityobj, *precipitationobj, *cityobj, *humidityobj, *pressureobj, *weatherobj, *lastupdateobj;

    FILE *fp;
    fp =fopen("weatherdata.txt","wt");

    if(fp==NULL){
	printf("파일 저장 실패\n");
	return 0;
    }


    myobj = json_object_new_object();

    headerobj = json_object_new_object();
    temperatureobj   = json_object_new_object();
    humidityobj   = json_object_new_object();
    pressureobj   = json_object_new_object();
    windobj   = json_object_new_object();
    windspeedobj   = json_object_new_object();
    winddirecobj   = json_object_new_object();
    cloudsobj   = json_object_new_object();
    visibilityobj   = json_object_new_object();
    precipitationobj   = json_object_new_object();
    cityobj   = json_object_new_object();
    weatherobj   = json_object_new_object();
    lastupdateobj   = json_object_new_object();

    //coord
    json_object_object_add(cityobj, "id", json_object_new_int(2643741));
    json_object_object_add(cityobj, "name", json_object_new_string("City Of LONDON"));
    json_object_object_add(headerobj, "lon", json_object_new_double(145.77));
    json_object_object_add(headerobj, "lat", json_object_new_double(-16.92));
    json_object_object_add(cityobj, "coord", headerobj);
    json_object_object_add(cityobj, "country", json_object_new_string("GB"));
    json_object_object_add(cityobj, "sunrise", json_object_new_string("2015-06-30T03:46:57"));
    json_object_object_add(cityobj, "sunset", json_object_new_string("2015-06-30T20:21:12"));
    json_object_object_add(myobj, "city", cityobj);

    //temperature
    json_object_object_add(temperatureobj, "value", json_object_new_double(72.34));
    json_object_object_add(temperatureobj, "min", json_object_new_double(66.2));
    json_object_object_add(temperatureobj, "max", json_object_new_double(79.88));
    json_object_object_add(temperatureobj, "unit", json_object_new_string("fahrenheit"));
    json_object_object_add(myobj, "temperature",temperatureobj);

    json_object_object_add(humidityobj, "value", json_object_new_int(43));
    json_object_object_add(humidityobj, "unit", json_object_new_string("%"));
    json_object_object_add(myobj,"humidity",humidityobj);

    json_object_object_add(pressureobj, "value", json_object_new_int(1020));
    json_object_object_add(pressureobj, "unit", json_object_new_string("hPa"));
    json_object_object_add(myobj, "pressure",pressureobj);

    //wind
    json_object_object_add(windspeedobj, "value", json_object_new_double(7.78));
    json_object_object_add(windspeedobj, "name", json_object_new_string("Moderate breeze"));
    json_object_object_add(windobj, "speed", windspeedobj);
    json_object_object_add(winddirecobj, "value", json_object_new_int(140));
    json_object_object_add(winddirecobj, "code", json_object_new_string("SE"));
    json_object_object_add(winddirecobj, "name", json_object_new_string("SouthEast"));
    json_object_object_add(windobj, "direction", winddirecobj);
    json_object_object_add(myobj, "wind", windobj);

    //clouds
    json_object_object_add(cloudsobj, "value", json_object_new_int(0));
    json_object_object_add(cloudsobj, "name", json_object_new_string("clear sky"));
    json_object_object_add(myobj, "clouds", cloudsobj);

    //visibility
    json_object_object_add(visibilityobj, "value", json_object_new_int(10000));
    json_object_object_add(myobj, "visibility", visibilityobj);

    // precipitation
    json_object_object_add(precipitationobj, "mode", json_object_new_string("no"));
    json_object_object_add(myobj, "precipitation", precipitationobj);

    //weather
    json_object_object_add(weatherobj, "number", json_object_new_int(800));
    json_object_object_add(weatherobj, "value", json_object_new_string("Sky is Clear"));
    json_object_object_add(weatherobj, "icon", json_object_new_string("01d"));
    json_object_object_add(myobj, "weather", weatherobj);

    //last update
    json_object_object_add(lastupdateobj, "value", json_object_new_string("2015-06-30T08:36:14"));
    json_object_object_add(myobj, "lastupdate", lastupdateobj);


    printf("myobj.to_string()=%s\n", json_object_to_json_string(myobj));

    fprintf(fp, "%s\n",json_object_to_json_string(myobj));
    fclose(fp);

    json_object_put(cityobj);
    json_object_put(weatherdataobj);
    json_object_put(myobj);
    json_object_put(temperatureobj);
    json_object_put(humidityobj);
    json_object_put(pressureobj);
    json_object_put(windobj);
    json_object_put(windspeedobj);
    json_object_put(winddirecobj);
    json_object_put(cloudsobj);
    json_object_put(visibilityobj);
    json_object_put(precipitationobj);
    json_object_put(weatherobj);
    json_object_put(lastupdateobj);
    return(0);
}
