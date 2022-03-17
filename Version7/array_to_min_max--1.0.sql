CREATE OR REPLACE FUNCTION 
array_to_min_max(anyarray)
RETURNS anyarray
AS 'array_to_min_max', 'array_to_min_max'
LANGUAGE c IMMUTABLE;
