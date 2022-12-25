<?php
 
    if(isset($_POST["creanodo"])){
        
        $nombre_nodo = $_POST["nombre_nodo"];
        $idnodo = $_POST["idnodo"];


        $url_rest = "http://localhost:3000/nodos/";
        $data = array(
            "idnodo" =>$idnodo,
            "nombre" =>  $nombre_nodo,
            
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