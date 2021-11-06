var Promise = require('bluebird');
var fs = Promise.promisifyAll(require('fs'));
var promises = [];

let index_html = ""
let index_html_length = 0

let app_js = ""
let app_js_length = 0

let favicon_ico = ""
let favicon_ico_length = 0

let font_woff = ""
let font_woff_length = 0

function convertToHex(data) {
    let value = "0x"
    let hexString = data
    for (let i=0; i < hexString.length; i++) {
         value +=hexString[i];
         if(i%2 == 1 && i<hexString.length-1)
            value += ",0x";
    }
    
    return {
        newData: value,
        length: hexString.length/2
    }
}

console.log("Đang đọc file")
promises.push(fs.readFileAsync("./dist/index.html.gz", 'hex')
.then((data)=>{
    let {newData, length} = convertToHex(data)
    index_html = newData
    index_html_length = length
    return Promise.resolve()
}))
promises.push(fs.readFileAsync("./dist/js/app.js.gz", 'hex')
.then( (data)=>{
    let {newData, length} = convertToHex(data)
    app_js = newData
    app_js_length = length
    return Promise.resolve()
    
}))
promises.push(fs.readFileAsync("./dist/static/favicon.ico.gz", 'hex')
.then( (data)=>{
    let {newData, length} = convertToHex(data)
    favicon_ico = newData
    favicon_ico_length = length
    return Promise.resolve()
}))
promises.push(fs.readFileAsync("./dist/fonts/element-icons.woff.gz", 'hex')
.then( (data)=>{
    let {newData, length} = convertToHex(data)
    font_woff = newData
    font_woff_length = length
    return Promise.resolve()
}))

Promise.all(promises).
finally(()=>{

    let content = `
#include <pgmspace.h>
static const char app_js[] PROGMEM = {${app_js}};
static const long app_js_length = ${app_js_length};
static const char index_html[] PROGMEM = {${index_html}};
static const long index_html_length = ${index_html_length};
static const char favicon_ico[] PROGMEM = {${favicon_ico}};
static const long favicon_ico_length = ${favicon_ico_length};
static const char font_woff[] PROGMEM = {${font_woff}};
static const long font_woff_length = ${font_woff_length};
    `
   
    console.log("Đang ghi file")

    fs.writeFile('../device/espVuejs/src/dist.h', content, 'utf8',async ()=>{
        console.log("Hoàn tất")
        
    })
})

   