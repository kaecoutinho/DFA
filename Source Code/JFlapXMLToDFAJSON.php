<?php
	// JFlapXMLToDFAJSON.h
	// Kaê Angeli Coutinho
	// MIT license

	$file = $_GET["file"];
	$name = $_GET["name"];
	$description = $_GET["description"];
	if(isset($file) && isset($name) && isset($description))
	{
		$xml = simplexml_load_file($file);
		$json["name"] = $name;
		$json["description"] = $description;
		$index = 0;
		$alphabet = "";
		foreach($xml->automaton->state as $state)
		{
			$json["states"][$index]["name"] = (string)$state["name"];
			$json["states"][$index]["id"] = (int)$state["id"];
			$json["states"][$index]["initial"] = (bool)isset($state->initial);
			$json["states"][$index]["final"] = (bool)isset($state->final);
			$json["states"][$index]["recognitionMessage"] = (isset($state->final) ? "recognition succeed" : "recognition failed");
			$json["states"][$index]["transitions"] = array();
			$index++;
		}
		$index = 0;
		foreach($xml->automaton->transition as $transition)
		{
			$currentSymbol = (string)$transition->read;
			if(strpos($alphabet,$currentSymbol) === FALSE)
			{
				$alphabet .= $currentSymbol;
			}
			$transitions[(string)$transition->from][$index]["symbol"] = $transitions[(string)$transition->from][$index]["symbol"] . $currentSymbol;
			foreach($json["states"] as $state)
			{
				if($state["id"] == (int)$transition->to)
				{
					$transitions[(string)$transition->from][$index]["destination"] = $state["name"];
					break;
				}
			}
			$index++;
		}
		$alphabetParts = str_split($alphabet);
		sort($alphabetParts);
		$alphabet = implode('',$alphabetParts);
		$json["alphabet"] = $alphabet;
		$index = 0;
		for($index = 0; $index < count($json["states"]); $index++)
		{
			if(isset($transitions[$json["states"][$index]["id"]]))
			{
				foreach($transitions[$json["states"][$index]["id"]] as $transition)
				{
					$json["states"][$index]["transitions"][] = $transition;
				}
			}
		}
		for($index = 0; $index < count($json["states"]); $index++)
		{
			for($transitionIndex = 0; $transitionIndex < count($json["states"][$index]["transitions"]); $transitionIndex++)
			{
				for($aux = 0; $aux < count($json["states"][$index]["transitions"]); $aux++)
				{
					if($aux != $transitionIndex)
					{
						if(strcmp($json["states"][$index]["transitions"][$transitionIndex]["destination"],$json["states"][$index]["transitions"][$aux]["destination"]) == 0)
						{
							$json["states"][$index]["transitions"][$transitionIndex]["symbol"] .= $json["states"][$index]["transitions"][$aux]["symbol"];
							array_splice($json["states"][$index]["transitions"],$aux--,1);
						}
					}
				}
			}
			for($transitionIndex = 0; $transitionIndex < count($json["states"][$index]["transitions"]); $transitionIndex++)
			{
				$symbolParts = str_split($json["states"][$index]["transitions"][$transitionIndex]["symbol"]);
				sort($symbolParts);
				$json["states"][$index]["transitions"][$transitionIndex]["symbol"] = implode('',$symbolParts);
			}
		}
		for($index = 0; $index < count($json["states"]); $index++)
		{
			unset($json["states"][$index]["id"]);
		}
		echo json_encode($json);
	}
	else
	{
		echo "<br/>Expects arguments<br/><br/>\t[file : string, name : string, description : string]<br/><br/>";
	}
?>
