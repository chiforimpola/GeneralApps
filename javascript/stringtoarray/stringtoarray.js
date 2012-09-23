

    function stringToArray(stringbuffer, pattern)
    {
        var aux = '';
        var values = Array();
        var ivalues = 0;

        for (i in stringbuffer)
        {
            if (stringbuffer[i] != pattern) aux += stringbuffer[i];

            else
            {
                values[ivalues] = aux;
                aux = '';
                ivalues += 1;
            }
        }
        values[ivalues] = aux;

        return (values);
    }

