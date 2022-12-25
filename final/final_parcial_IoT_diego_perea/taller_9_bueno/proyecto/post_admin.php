<?php
 
    if(isset($_POST["posti"])){
        
        $u = $_POST["usuario"];
        $p = $_POST["pass"];
        $r = $_POST["rol"];
        $n = $_POST["nodo"];


        $url_rest = "http://localhost:3000/usuarios";
        $data = array(
            "user" => $u,
            "password" => $p,
            "rol"=>$r,
            "idnodo" => $n
        );
        $data_string = json_encode($data);
        $curl = curl_init($url_rest);

        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_setopt($curl, CURLOPT_POSTFIELDS, $data_string);
        curl_setopt($curl, CURLOPT_HEADER, true);
        curl_setopt($curl, CURLOPT_HTTPHEADER,
            array(
                'Content-Type:application/json',
                'Content-Length: ' . strlen($data_string)
            )
        );

        $result = curl_exec($curl);
         
        
         header("Location: home.php"); 
    }
    else{
       
          }

        
   

?>   