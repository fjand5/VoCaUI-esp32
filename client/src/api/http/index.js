import axios from 'axios'
let getUrl = window.location;

const esp8266 = axios.create({
  // baseURL: 'http://192.168.1.10',
  baseUrl : getUrl .protocol + "//" + getUrl.hostname + "/"
});
// Add a request interceptor
esp8266.interceptors.request.use(function (config) {
  // Do something before request is sent
  if (config.headers.Authorization){
    // config.headers.Authorization = config.headers.Authorization
  }
  else {
    config.headers.Authorization = localStorage.getItem('jwt_aut', "")

  }
  return config;
}, function (error) {
  // Do something with request error
  return Promise.reject(error);
});

// Add a response interceptor
esp8266.interceptors.response.use(function (response) {
  // Any status code that lie within the range of 2xx cause this function to trigger
  // Do something with response data
  if (response.data)
    return Promise.resolve(response.data)
  return Promise.resolve(response);
}, function (error) {
  // Any status codes that falls outside the range of 2xx cause this function to trigger
  // Do something with response error
  return Promise.reject(error);
});
export default esp8266;