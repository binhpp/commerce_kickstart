<?php 

/**
 * exception class used during HTTP response processing
 * @author Nam Pham
 *
 */
class RemoteRestException extends Exception {
	protected $remoteCode;
	protected $remoteTrace;
	
	public function __construct($json) {
		$parts = explode('.',$json->class);
		$this->remoteCode = $parts[count($parts)-1];
		$this->remoteTrace = $json->trace;
		
		parent::__construct($json->message);
	}
	
	public function getRemoteCode() {
		return $this->remoteCode;
	}
	
	public function getRemoteTrace() {
		return $this->remoteTrace;
	}
}

/**
 * fake http/Client/Request
 * @author Nam Pham
 *
 */
class RestDrupalRequest {
	protected $options;
	
	public function __construct($options) {
		$this->options = $options;
	}
	
	public function setContentType($contentType) {
		$this->setHeader('Content-Type', $contentType);
	}
	
	public function getOptions() {
		return $this->options;
	}
	
	/**
	 * set query string
	 * @param mixed $params
	 */
	public function setQuery($params) {
		$url = $this->options['url'];
		$quest = strpos($url, '?');
		if ($quest===FALSE) {
			$query = '';
		}
		else {
			$query = substr($url, $quest + 1);
			$url = substr($url, 0, $quest);
		}
		
		if (is_array($params)) {
			foreach ($params as $name => $value)
				$query .= (strlen($query)>0?'&':'').$name.'='.urlencode($value);
		}
		else {
			$query .= '&'.$params;
		}
		
		$this->options['url'] = $url.'?'.$query;
	}
	
	/**
	 * set HTTP Header value, NULL means remove
	 * @param string $header
	 * @param string $value
	 */
	public function setHeader($header, $value) {
		if (is_null($value))
			unset($this->options['headers'][$header]);
		else
			$this->options['headers'][$header] = $value;
	}
}

/**
 * fake http/Client/Response
 * @author Nam Pham
 *
 */
class RestDrupalResponse {
	// stdClass return by drupal_http_request
	protected $data;
	
	public function __construct(&$data) {
		$this->data = $data;
		if (isset($this->data->error) && empty($this->data->data))
			$this->data->data = $this->data->error;
	}
	
	public function getResponseCode() {
		return $this->data->code;
	}
	
	public function getHeader($header) {
		$header = strtolower($header);
		return isset($this->data->headers[$header])?$this->data->headers[$header]:null;
	}
	
	public function getBody() {
		return new RestDrupalBody($this->data->data);
	}
}

/**
 * fake http/Message/Body
 * @author Nam Pham
 *
 */
class RestDrupalBody {
	protected $data;
	
	public function __construct(&$data) {
		$this->data = $data;
	}
	
	public function toString() {
		return $this->data;
	}
}

/**
 * fake http/Client
 * @author Nam Pham
 *
 */
class RestDrupalClient {
	protected $options;
	protected $reqList = array();
	protected $resList = array();
	
	public function __construct($options) {
		$this->options = $options;
	}
	
	public function enqueue($request, $callback = NULL) {
		$this->reqList[] = $request;
	}
	
	public function count() {
		return count($this->reqList);
	}
	
	public function send() {
		foreach ($this->reqList as &$request) {
			$req = array_merge($this->options, $request->getOptions());
			if (isset($this->options['useragent']) && !isset($req['headers']['User-Agent']))
				$req['headers']['User-Agent'] = $this->options['useragent'];
			$res = drupal_http_request($req['url'], $req);
			$this->resList[] = new RestDrupalResponse($res);
		}
	}
	
	public function getResponse() {
		return array_shift($this->resList);
	}
}