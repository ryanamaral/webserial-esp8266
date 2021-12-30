#include <pgmspace.h>
char style_css[] PROGMEM = R"=====(
:root{--blue:#375a7f;--indigo:#6610f2;--purple:#6f42c1;--pink:#e83e8c;--red:#E74C3C;--orange:#fd7e14;--yellow:#F39C12;--green:#00bc8c;--teal:#20c997;--cyan:#3498DB;--white:#fff;--gray:#999;--gray-dark:#303030;--primary:#375a7f;--secondary:#444;--success:#00bc8c;--info:#3498DB;--warning:#F39C12;--danger:#E74C3C;--light:#303030;--dark:#adb5bd;--breakpoint-xs:0;--breakpoint-sm:576px;--breakpoint-md:768px;--breakpoint-lg:992px;--breakpoint-xl:1200px;--font-family-sans-serif:"Lato", -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";--font-family-monospace:SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;}
*,*::before,*::after{-webkit-box-sizing:border-box;box-sizing:border-box;}
html{font-family:sans-serif;line-height:1.15;-webkit-text-size-adjust:100%;-webkit-tap-highlight-color:rgba(0,0,0,0);}
body{margin:0;font-family:"Lato", -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";font-size:0.9375rem;font-weight:400;line-height:1.5;color:#fff;text-align:left;background-color:#222;}
h4{margin-top:0;margin-bottom:0.5rem;}
p{margin-top:0;margin-bottom:1rem;}
button{border-radius:0;}
button:focus{outline:1px dotted;outline:5px auto -webkit-focus-ring-color;}
button{margin:0;font-family:inherit;font-size:inherit;line-height:inherit;}
button{overflow:visible;}
button{text-transform:none;}
button{-webkit-appearance:button;}
button::-moz-focus-inner{padding:0;border-style:none;}
h4{margin-bottom:0.5rem;font-weight:500;line-height:1.2;}
h4{font-size:1.40625rem;}
.container{width:100%;padding-right:15px;padding-left:15px;margin-right:auto;margin-left:auto;}
@media (min-width: 576px){
.container{max-width:540px;}
}
@media (min-width: 768px){
.container{max-width:720px;}
}
@media (min-width: 992px){
.container{max-width:960px;}
}
@media (min-width: 1200px){
.container{max-width:1140px;}
}
.btn{display:inline-block;font-weight:400;color:#fff;text-align:center;vertical-align:middle;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;background-color:transparent;border:1px solid transparent;padding:0.375rem 0.75rem;font-size:0.9375rem;line-height:1.5;border-radius:0.25rem;-webkit-transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;}
@media (prefers-reduced-motion: reduce){
.btn{-webkit-transition:none;transition:none;}
}
.btn:hover{color:#fff;text-decoration:none;}
.btn:focus{outline:0;-webkit-box-shadow:0 0 0 0.2rem rgba(55,90,127,0.25);box-shadow:0 0 0 0.2rem rgba(55,90,127,0.25);}
.btn:disabled{opacity:0.65;}
.btn-primary{color:#fff;background-color:#375a7f;border-color:#375a7f;}
.btn-primary:hover{color:#fff;background-color:#2b4764;border-color:#28415b;}
.btn-primary:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(85,115,146,0.5);box-shadow:0 0 0 0.2rem rgba(85,115,146,0.5);}
.btn-primary:disabled{color:#fff;background-color:#375a7f;border-color:#375a7f;}
.btn-success{color:#fff;background-color:#00bc8c;border-color:#00bc8c;}
.btn-success:hover{color:#fff;background-color:#009670;border-color:#008966;}
.btn-success:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(38,198,157,0.5);box-shadow:0 0 0 0.2rem rgba(38,198,157,0.5);}
.btn-success:disabled{color:#fff;background-color:#00bc8c;border-color:#00bc8c;}
.btn-warning{color:#fff;background-color:#F39C12;border-color:#F39C12}
.btn-warning:hover{color:#fff;background-color:#d4860b;border-color:#c87f0a}
.btn-warning:focus,.btn-warning.focus{-webkit-box-shadow:0 0 0 0.2rem rgba(245,171,54,0.5);box-shadow:0 0 0 0.2rem rgba(245,171,54,0.5)}
.btn-warning:disabled{color:#fff;background-color:#F39C12;border-color:#F39C12;}
.btn-danger{color:#fff;background-color:#E74C3C;border-color:#E74C3C;}
.btn-danger:hover{color:#fff;background-color:#e12e1c;border-color:#d62c1a;}
.btn-danger:focus{-webkit-box-shadow:0 0 0 0.2rem rgba(235,103,89,0.5);box-shadow:0 0 0 0.2rem rgba(235,103,89,0.5);}
.btn-danger:disabled{color:#fff;background-color:#E74C3C;border-color:#E74C3C;}
.navbar{position:relative;display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;padding:1rem 1rem;}
.navbar>.container{display:-webkit-box;display:-ms-flexbox;display:flex;-ms-flex-wrap:wrap;flex-wrap:wrap;-webkit-box-align:center;-ms-flex-align:center;align-items:center;-webkit-box-pack:justify;-ms-flex-pack:justify;justify-content:space-between;}
.navbar-brand{display:inline-block;padding-top:0.32421875rem;padding-bottom:0.32421875rem;margin-right:1rem;font-size:1.171875rem;line-height:inherit;white-space:nowrap;}
.navbar-brand:hover,.navbar-brand:focus{text-decoration:none;}
@media (max-width: 991.98px){
.navbar-expand-lg>.container{padding-right:0;padding-left:0;}
}
@media (min-width: 992px){
.navbar-expand-lg{-webkit-box-orient:horizontal;-webkit-box-direction:normal;-ms-flex-flow:row nowrap;flex-flow:row nowrap;-webkit-box-pack:start;-ms-flex-pack:start;justify-content:flex-start;}
.navbar-expand-lg>.container{-ms-flex-wrap:nowrap;flex-wrap:nowrap;}
}
.navbar-dark .navbar-brand{color:#fff;}
.navbar-dark .navbar-brand:hover,.navbar-dark .navbar-brand:focus{color:#fff;}
.card{position:relative;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:vertical;-webkit-box-direction:normal;-ms-flex-direction:column;flex-direction:column;min-width:0;word-wrap:break-word;background-color:#303030;background-clip:border-box;border:1px solid rgba(0,0,0,0.125);border-radius:0.25rem;}
.card-body{-webkit-box-flex:1;-ms-flex:1 1 auto;flex:1 1 auto;padding:1.25rem;}
.card-title{margin-bottom:0.75rem;}
.card-text:last-child{margin-bottom:0;}
.badge{display:inline-block;padding:0.25em 0.4em;font-size:75%;font-weight:700;line-height:1;text-align:center;white-space:nowrap;vertical-align:baseline;border-radius:0.25rem;-webkit-transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;transition:color 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-box-shadow 0.15s ease-in-out;}
@media (prefers-reduced-motion: reduce){
.badge{-webkit-transition:none;transition:none;}
}
.badge:empty{display:none;}
.badge-success{color:#fff;background-color:#00bc8c;}
.badge-danger{color:#fff;background-color:#E74C3C;}
.bg-primary{background-color:#375a7f!important;}
.mr-3{margin-right:1rem!important;}
.mb-3{margin-bottom:1rem!important;}
@media print{
*,*::before,*::after{text-shadow:none!important;-webkit-box-shadow:none!important;box-shadow:none!important;}
p{orphans:3;widows:3;}
body{min-width:992px!important;}
.container{min-width:992px!important;}
.navbar{display:none;}
.badge{border:1px solid #000;}
}
textarea {
  width:100%;
  margin: 0;
  font-family: inherit;
  font-size: inherit;
  line-height: inherit;
}
textarea {
  overflow-y: scroll;
  resize: vertical;
}
textarea.form-control {
  height: auto;
}
input:focus,textarea:focus{
 outline: none;
}
)=====";
