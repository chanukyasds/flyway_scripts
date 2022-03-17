#include <postgres.h>
#include <fmgr.h>
#include <utils/array.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

PG_MODULE_MAGIC;

Datum min_to_max(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(min_to_max);


Datum
min_to_max(PG_FUNCTION_ARGS)
{
  // The formal PostgreSQL array objects:
  ArrayType *array1;

  // The array element types (should always be INT4OID):
  Oid arrayElementType1= get_fn_expr_argtype(fcinfo->flinfo, 0);

  // The array element type widths (should always be 4):
  int16 arrayElementTypeWidth1;

  // The array element type "is passed by value" flags (not used, should always be true):
  bool arrayElementTypeByValue1;

  // The array element type alignment codes (not used):
  char arrayElementTypeAlignmentCode1;

  // The array contents, as PostgreSQL "datum" objects:
  Datum *arrayContent1;

  // List of "is null" flags for the array contents:
  bool *arrayNullFlags1;

  // The size of each array:
  int arrayLength1;

  char str,min_str,max_str;
  int i,min,max;
  

  if (PG_ARGISNULL(0))
    ereport(ERROR, (errmsg("Null array not accepted")));

  array1 = PG_GETARG_ARRAYTYPE_P(0);
  

  if (ARR_NDIM(array1) != 1)
    ereport(ERROR, (errmsg("One-dimesional arrays are required")));

  arrayLength1 = (ARR_DIMS(array1))[0];
  
  if (array_contains_nulls(array1))
    ereport(ERROR, (errmsg("Array contains null elements")));

  // Determine the array element types.
  arrayElementType1 = ARR_ELEMTYPE(array1);
  get_typlenbyvalalign(arrayElementType1, &arrayElementTypeWidth1, &arrayElementTypeByValue1, &arrayElementTypeAlignmentCode1);

  // Extract the array contents (as Datum objects).
  deconstruct_array(array1, arrayElementType1, arrayElementTypeWidth1, arrayElementTypeByValue1, arrayElementTypeAlignmentCode1,
&arrayContent1, &arrayNullFlags1, &arrayLength1);


/*
  min=max=arrayContent1[0];


  // Generate the sums.
  for (i = 0; i < arrayLength1; i++)
  {
    if(min>arrayContent1[i])
      min=arrayContent1[i];
   if(max<arrayContent1[i])
      max=arrayContent1[i];
  }

sprintf(min_str, "%c", min);
sprintf(max_str, "%c", max);

strcpy(str,min_str);
strcpy(str,"->");
strcpy(str,max_str);
*/

PG_RETURN_TEXT_P("HELLO"); 

return 0;
}

