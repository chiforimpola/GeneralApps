
<?php

/*
* A ideia e ter uma classe que centralize o acesso ao banco, de modo que se algo der errado
* eu sei onde esta localizado o erro
*/

define ('QUERY_ASSOC', 0);
define ('QUERY_ARRAY', 1);

  class DatabaseController
  {
      private $server = null;
      private $base = null;
      private $login = null;
      private $pwd = null;
      private $database = null;

      private $connection = null;

      public function __construct ($server = null, $login = null, $pwd = null, $database = null)
      {
          if (!is_null($server) && !is_null($login) && !is_null ($pwd))
              $this->Connect($server, $login, $pwd);
          if (!is_null($database)) $this->setDatabase ($database);

          return ($this->connection);
      }

      public function getConnectionHandler (){ return ($this->connection); }

      public function setServer ($server){ $this->server = $server; return ($this); }
      public function getServer (){ return ($this->server); }

      public function setLogin ($login){ $this->login = $login; return ($this); }
      public function getLogin (){  return ($this->login);  }

      public function setPassword($password){ $this->pwd = $password; return ($this); }
      public function getPassword(){ return ($this->pwd); }

      public function setDatabase ($base){ $this->database = $base; if (!is_null($this->getConnectionHandler())) mysql_select_db($this->base); return ($this); } 
      public function getDatabase(){ return ($this->database); }

      public function executeQuery ($query, $mode = QUERY_ASSOC)
      {
          $rows = Array ();
          $queryresult = mysql_query ($query);

          if ($mode == QUERY_ASSOC) while ($row = mysql_fetch_assoc($queryresult)) $rows[] = $row;
          else if ($mode == QUERY_ARRAY) while ($row = mysql_fetch_array ($queryresult) ) $rows[] = $row;

          return ($rows);
      }

      public function connect($server=null, $login=null, $password=null)
      {
          if (
                 is_null($this->getServer()) && is_null($server) ||
                 is_null($this->getLogin()) && is_null($login) ||
                 is_null($this->getPassword()) && is_null($password)
             )
             return (null);

          if (is_null($this->getServer())) $this->setServer($server);
          if (is_null($this->getLogin())) $this->setLogin($login);
          if (is_null($this->getPassword())) $this->setPassword($password);

          $this->connection = mysql_connect ($this->getServer(), $this->getLogin(), $this->getPassword());

          if (!is_null($this->getDatabase())) mysql_select_db($this->getDatabase());

          return ($this);
      }

      public function __tostring(){ return (get_class($this)); }
  }
?>

