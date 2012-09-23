
<?php
    function getTree($path, $maxdepth)
    {
        $actualDir = ".";
        $backDir = "..";
        $objs = scandir ($path);
        $results = Array();
        if (is_array ($objs) && sizeof ($objs) > 0)
        {
            if ($path[strlen($path)-1] != '/') $path .= '/';

            foreach ($objs as $obj)
            {
                if ($maxdepth == 0) break;

                else if ($obj != $actualDir && $obj != $backDir)
                {
                    $results[] =  $path .  $obj;

                    if (is_dir ($path . $obj))
                    {
                        $aux = getTree ($path . $obj, $maxdepth - 1);
                        
                        foreach ($aux as $a) $results[] = $a;
                    }
                }
            }
        }
        return ($results);
    }

    if (count($argv) < 3)
    {
        print ("\n<maxdepth>\n<dirPath>\n");
    }
    else
    {
        $results = Array ();
        for($index=1;$index<count($argv);$index+=2)
        {
            $results[] = getTree ($argv[$index+1], $argv[$index]);
        }
        for ($i=0;$i<count($results);$i++)
        {
            var_dump ($results[$i]);
        }
    }
?>


