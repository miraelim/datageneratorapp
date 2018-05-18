#include <stdio.h>
#include <json-c/json.h>
#include <string.h>

int main(int argc, char **argv)
{
    json_object *myobj1, *schemaobj1, *descriptionobj1, *typeobj1, *reference1, *defobj1, *propertiesobj1, *reqobj1;
    json_object *dobj,*darray, *dval;



    FILE *fp1;
    char weatherdata[1024];
    fp1 =fopen("weather.json","rt");

    if(fp1==NULL){
	printf("파일 읽기  실패\n");
	return 0;
    }

    while(!feof(fp1))
    {
	fgets(weatherdata, 1024, fp1);
    }

    weatherobj1 = json_tokener_parse(weatherdata);
    

    myobj = json_object_new_object();
    schemaobj = json_object_new_object();
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
