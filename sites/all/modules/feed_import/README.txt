FEED IMPORT

Project page: http://drupal.org/project/feed_import
Examples: http://drupal.org/node/1360374

------------------------------
Features
------------------------------

  -easy to use interface
  -alternative xpaths support and default value
  -ignore field & skip item import
  -multi value fields support
  -pre-filters & filters
  -some usefull provided filters
  -auto-import/delete at cron
  -import in specified time interval
  -import/export feed configuration
  -reports
  -add taxonomy terms to field (can add new terms)
  -process HTML pages
  -process CSV files
  -add image to field (used as filter)
  -custom settings on each feed process function
  -do not save info about imported items (usually used for one-time import)

------------------------------
About Feed Import
------------------------------

Feed Import module allows you to import content from XML/HTML/CSV files into
entities (like node, user, ...) using XPATH to fetch whatever you need.
You can create a new feed using php code in your module or you can use the
provided UI (recommended). If you have regular imports you can enable import
to run at cron. Now Feed Import provides four methods to process files:
    Normal  - loads the XML file with simplexml_load_file() and parses
              it's content. This method isn't good for huge files because
              needs very much memory.
    Chunked - gets chunks from XML file and recompose each item. This is a good
              method to import huge xml files. This cannot be used if parent
              xpath is based on properties. You cannot use parent xpath like
              //category[@type="new"]/items
              or
              //category/items[@posted="today"]
              but you can use xpaths like
              //category/items.
              Fields xpaths are normally.
    Reader  - reades xml file node by node and imports it. The parent xpath is
              limited to one attribute (the complex is something like
              //tagname[@attribute="value for this attribute"]).
    HTML    - converts HTML document to xml and then is imported like a normal
              xml file.
    CSV     - loads content line by line and imports it.

------------------------------
How Feed Import works
------------------------------

Step 1: Downloading xml file and creating items

  -if we selected processXML function for processing this feed then all
   xml file is loaded. We apply parent xpath, we create entity objects and we
   should have all items in an array.
  -if we selected processXMLChunked function for processing then xml file is
   read in chunks. When we have an item we create the SimpleXMLElement object
   and we create entity object. We delete from memory content read so far and we
   repeat process until all xml content is processed.
  -if we selected processXmlReader then xml is read node by node and imported.
  -if we selected processHTMLPage function then HTML is converted to XML and
   imported like processXML.
  -if we selected processCSV function then file is read line by line and
   imported.
  -if we selected another process function then we should take a look at that
   function

Step 2: Creating entities

Well this step is contained in Step 1 to create entity objects from
SimpleXMLElement objects using feed info:
We generate an unique hash for item using unique xpath from feed. Then for each
field in feed we apply xpaths until one xpath passes pre-filter. If there is an
xpath that passed we take the value and filter it. If filtered value is empty
(or isn't a value) we use default action/value. In this mode we can have
alternative xpaths. Example:

<Friends>
  <Friend type="bestfriend">Jerry</Friend>
  <Friend type="normal">Tom</Friend>
</Friends>

Here we can use the following xpaths to take friend name:
Friends/Friend[@type="bestfriend"]
Friends/Friend[@type="normal"]

If bestfriend is missing then we go to normal friend. If normal friend is
missing too, we can specify a default value like "Forever alone".

Step 3: Saving/Updating entities

First we get the IDs of generated hashes to see if we need to create a new
entity or just to update it.
For each object filled with data earlier we check the hash:
  -if hash is in IDs list then we check if entity data changed to see if we have
   to save changes or just to update the expire time.
  -if hash isn't in list then we create a new entity and hash needs to be
   inserted in database.
If is a one-time import then none of the items info is saved. This can produce
duplicate content.

Feed Import can add multiple values to fields which support this. For example
above we need only one xpath:
Friends/Friend
and both Tom and Jerry will be inserted in field values, which is great.
Now you can specify not only the column value but the entire array of values by
returning an object from filter functions.

Expire time is used to automatically delete entities (at cron) if they are
missing from feed for more than X seconds.
Expire time is updated for each item in feed. For performance reasons we make a
query for X items at once to update or insert.

------------------------------
Using Feed Import UI
------------------------------

First, navigate to admin/config/services/feed_import. You can change global
settings using "Settings" link. To add a new feed click "Add new feed" link and
fill the form with desired data. After you saved feed click "Edit" link from
operations column. Now at the bottom is a fieldset with XPATH settings. Add
XPATH for required item parent and unique id (you can now save feed). To add a
new field choose one from "Add new field" select and click "Add selected field"
button. A fieldset with field settings appeared and you can enter xpath(s) and
default action/value. If you wish you can add another field and when you are
done click "Save feed" submit button.
Check if all fields are ok. If you want to (pre)filter values select
"Edit (pre)filter" tab. You can see a fieldset for each selected field. Click
"Add new filter" button for desired field to add a new filter. Enter unique
filter name per field (this can be anything that let you quickly identify
filter), enter function name (any php function, even static functions
ClassName::functionName) and enter parameters for function, one per line.
To send field value as parameter enter [field] in line. There are some static
filter functions in feed_import_filter.inc.php file >> class FeedImportFilter
that you can use. Please take a look. I'll add more soon.
If you want to change [field] with somenthing else go to Settings.
You can add/remove any filters you want but don't forget to click "Save filters"
submit button to save all.
Now you can enable feed and test it.

------------------------------
Feed Import API
------------------------------

If you want, you can use your own function to parse content. To do that you have
to implement hook_feed_import_process_info() which returns an array keyed by
function alias and with value of another array containing following keys:
  function => Function name for processing. If function is a static member of a
              class then value is an array containing class name and function
              name. This function gets as parameter an array with feed info.
  settings => An array containing settings for process function keyed by setting
              name. A setting is an array with following keys and values:
                title       =>  This is displayed like textfield title.
                description =>  This is displayed as textfield description.
                default     =>  This is default SCALAR value for setting.
              If function doesn't need user settings then this is must be an
              empty array.
  validate => A function name (like "function" key above) which will validate
              all settings. Function gets as parameters: setting name, value and
              default value. If setting value isn't valid then function must
              return default value else return value. This function is called
              for every setting so you may have to use a switch statement.
              If you don't want to use this set it to NULL.
  info     => Some text describing process function, settings and others.

Please note that in process function EVERY possible exception MUST BE CAUGHT!

Example:
function hook_feed_import_process_info() {
  return array(
    'processFeedSuperFast' => array(
      'function' => 'php_process_function_name',
      'settings' => array(
        'my_setting' => array(
          'title' => t('Setting title'),
          'description' => t('My setting description'),
          'default' => 128,
        ),
        'other_setting' => array(
          'title' => t('The other setting'),
          'description' => t('Description for setting'),
          'default' => 'abcd',
        ),
        // Other settings...
      ),
      'validate' => 'php_process_function_validate',
      'info' => t('About this process function.'),
    ),
    // Other functions ...
  );
}

Every function is called with a parameter containing feed info and must return
an array of objects (stdClass). For example above we will have:

/**
 * Process feed function.
 */
function php_process_function_name(array $feed) {
  $items = array();
  // We can use settings like this:
  $my_setting = $feed['xpath']['settings']['my_setting'];
  $other_setting = $feed['xpath']['settings']['other_setting'];

  // ...
  // Here process feed items.
  // ...
  return $items;
}

/**
 * Callback for validate.
 */
function php_process_function_validate($name, $value, $default) {
  switch ($name) {
    case 'my_setting':
      if ($value < 10) {
        // Well, if you want you can use drupal_set_message('msg', 'warning') to
        // tell user that his value isn't valid
        drupal_set_message(t('Value must be at least 10!'), 'warning');
        return $default;
      }
      break;
    case 'other_setting':
      if ($value = 'xyz') {
        $value = 'test';
      }
      break;
  }
  return $value;
}

Please check source code for a good example.

------------------------------
Feed info structure
------------------------------

Feed info is an array containing all info about feeds: name, url, xpath keyed
by feed name.
A feed is an array containing the following keys:

id => This is feed unique id

machine_name => This is feed unique machine name

name => This is feed name

enabled => Shows if feed is enabled or not. Enabled feeds are processed at cron
           if import at cron option is activated from settings page.

url => URL to xml file. To avoid problems use an absolute url.

time => This contains feed items lifetime. If 0 then items are kept forever else
        items will be deleted after this time is elapse and they don't exist
        in xml file anymore. On each import existing items will be rescheduled.

entity_info => This is an array containing two elements

  #entity => Entity name like node, user, ...

  #table_pk => This is entity's table index. For node is nid, for
               user si uid, ...


xpath => This is an array containing xpath info and fields

  #root => This is XPATH to parent item. Every xpath query will run in
           this context.

  #uniq => This is XPATH (relative to #root xpath) to a unique value
           which identify the item. Resulted value is used to create a
           hash for item so this must be unique per item.

  #process_function => This is function alias used to process xml file.
                       See documentation above about process functions.

  #settings => This is an array containing settings for process function keyed
               by setting name.

  #items => This is an array containing xpath for fields and filters keyed by
            field name.
    [field_name] => An array containing info about field, xpath, filters

      #field => This is field name

      #column => This is column in field table. For body is value, for taxonomy
                 is tid and so on. If this field is a column in entity field
                 then this must be NULL.

      #xpath => This is an array containig xpaths for this field. Xpaths are
                used from first to last until one passes pre-filter functions.
                All xpaths are relative to #root.

      #default_value => This is default value for field if none of xpaths passes
                        pre-filter functions. This is used only for
                        default_value and default_value_filtered actions.

      #default_action => Can be one of (see FeedImport::getDefaultActions()):
          default_value           -field will have this value
          default_value_filtered  -field will have this value after was filtered
          ignore_field            -field will have no value
          skip_item               -item will not be imported

      #filter => An array containing filters info keyed by filter name
        [filter_name] => An array containing filter function and params
          #function => This is function name. Can also be a public static
                       function from a class with value ClassName::functionName
          #params => An array of parameters which #function recives. You can use
                     [field] (this value can be changed from settings page) to
                     send current field value as parameter.

      #pre_filter => Same as filter, but these functions are used to pre-filter
                     values to see if we have to choose an alternative xpath.


To see a real feed array, first create some feeds using UI and then you can use
code below to print its structure:
$feeds = FeedImport::loadFeeds();
drupal_set_message('<pre>' . print_r($feeds, TRUE) . '</pre>');

If you want to modify feed just before import process you can implement
hook_feed_import_feed_info_alter(&$feed) hook.
