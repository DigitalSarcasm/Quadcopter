


<!DOCTYPE html>
<html lang="en" class="">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta http-equiv="Content-Language" content="en">
    
    
    <title>simple-jQuery-slider/transit.js at master · dirkgroenen/simple-jQuery-slider · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub">
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub">
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png">
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png">
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png">
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png">
    <meta property="fb:app_id" content="1401488693436528">

      <meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="dirkgroenen/simple-jQuery-slider" name="twitter:title" /><meta content="simple-jQuery-slider - Simple jQuery CSS3 slider. Simple to use and supports every browser! (IE7+)" name="twitter:description" /><meta content="https://avatars1.githubusercontent.com/u/1001391?v=3&amp;s=400" name="twitter:image:src" />
      <meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="https://avatars1.githubusercontent.com/u/1001391?v=3&amp;s=400" property="og:image" /><meta content="dirkgroenen/simple-jQuery-slider" property="og:title" /><meta content="https://github.com/dirkgroenen/simple-jQuery-slider" property="og:url" /><meta content="simple-jQuery-slider - Simple jQuery CSS3 slider. Simple to use and supports every browser! (IE7+)" property="og:description" />
      <meta name="browser-stats-url" content="/_stats">
    <link rel="assets" href="https://assets-cdn.github.com/">
    
    <meta name="pjax-timeout" content="1000">
    

    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="selected-link" value="repo_source" data-pjax-transient>
      <meta name="google-analytics" content="UA-3769691-2">

    <meta content="collector.githubapp.com" name="octolytics-host" /><meta content="collector-cdn.github.com" name="octolytics-script-host" /><meta content="github" name="octolytics-app-id" /><meta content="897A4022:7936:409DA3A:55197D3C" name="octolytics-dimension-request_id" />
    
    <meta content="Rails, view, blob#show" name="analytics-event" />

    
    <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico">


    <meta content="authenticity_token" name="csrf-param" />
<meta content="E/VQwEBGwmdwwnMIVguUxwI2Wn8VOMWriTibLLMATzYnX/zGJEnZQWRXqXBa8mc5SXbQde3Cc6xhATlDHbeJgg==" name="csrf-token" />

    <link href="https://assets-cdn.github.com/assets/github-6337179a282bad7457c5b97336a91ca3743e26d9564ce4c54d4baef4163fc364.css" media="all" rel="stylesheet" />
    <link href="https://assets-cdn.github.com/assets/github2-1b541813bef149ffc2f5118b0bfa467e9fe56083241b6a9f140d30ea692aefdc.css" media="all" rel="stylesheet" />
    
    


    <meta http-equiv="x-pjax-version" content="f82dd05eac900f987444c3b4e32e7dab">

      
  <meta name="description" content="simple-jQuery-slider - Simple jQuery CSS3 slider. Simple to use and supports every browser! (IE7+)">
  <meta name="go-import" content="github.com/dirkgroenen/simple-jQuery-slider git https://github.com/dirkgroenen/simple-jQuery-slider.git">

  <meta content="1001391" name="octolytics-dimension-user_id" /><meta content="dirkgroenen" name="octolytics-dimension-user_login" /><meta content="14956664" name="octolytics-dimension-repository_id" /><meta content="dirkgroenen/simple-jQuery-slider" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="false" name="octolytics-dimension-repository_is_fork" /><meta content="14956664" name="octolytics-dimension-repository_network_root_id" /><meta content="dirkgroenen/simple-jQuery-slider" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/dirkgroenen/simple-jQuery-slider/commits/master.atom" rel="alternate" title="Recent Commits to simple-jQuery-slider:master" type="application/atom+xml">

  </head>


  <body class="logged_out  env-production macintosh vis-public page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>
    <div class="wrapper">
      
      
      


        
        <div class="header header-logged-out" role="banner">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/" data-ga-click="(Logged out) Header, go to homepage, icon:logo-wordmark">
      <span class="mega-octicon octicon-logo-github"></span>
    </a>

    <div class="header-actions" role="navigation">
        <a class="btn btn-primary" href="/join" data-ga-click="(Logged out) Header, clicked Sign up, text:sign-up">Sign up</a>
      <a class="btn" href="/login?return_to=%2Fdirkgroenen%2Fsimple-jQuery-slider%2Fblob%2Fmaster%2Fsrc%2Ftransit.js" data-ga-click="(Logged out) Header, clicked Sign in, text:sign-in">Sign in</a>
    </div>

    <div class="site-search repo-scope js-site-search" role="search">
      <form accept-charset="UTF-8" action="/dirkgroenen/simple-jQuery-slider/search" class="js-site-search-form" data-global-search-url="/search" data-repo-search-url="/dirkgroenen/simple-jQuery-slider/search" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
  <input type="text"
    class="js-site-search-field is-clearable"
    data-hotkey="s"
    name="q"
    placeholder="Search"
    data-global-scope-placeholder="Search GitHub"
    data-repo-scope-placeholder="Search"
    tabindex="1"
    autocapitalize="off">
  <div class="scope-badge">This repository</div>
</form>
    </div>

      <ul class="header-nav left" role="navigation">
          <li class="header-nav-item">
            <a class="header-nav-link" href="/explore" data-ga-click="(Logged out) Header, go to explore, text:explore">Explore</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="/features" data-ga-click="(Logged out) Header, go to features, text:features">Features</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="https://enterprise.github.com/" data-ga-click="(Logged out) Header, go to enterprise, text:enterprise">Enterprise</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="/blog" data-ga-click="(Logged out) Header, go to blog, text:blog">Blog</a>
          </li>
      </ul>

  </div>
</div>



      <div id="start-of-content" class="accessibility-aid"></div>
          <div class="site" itemscope itemtype="http://schema.org/WebPage">
    <div id="js-flash-container">
      
    </div>
    <div class="pagehead repohead instapaper_ignore readability-menu">
      <div class="container">
        
<ul class="pagehead-actions">

  <li>
      <a href="/login?return_to=%2Fdirkgroenen%2Fsimple-jQuery-slider"
    class="btn btn-sm btn-with-count tooltipped tooltipped-n"
    aria-label="You must be signed in to watch a repository" rel="nofollow">
    <span class="octicon octicon-eye"></span>
    Watch
  </a>
  <a class="social-count" href="/dirkgroenen/simple-jQuery-slider/watchers">
    17
  </a>

  </li>

  <li>
      <a href="/login?return_to=%2Fdirkgroenen%2Fsimple-jQuery-slider"
    class="btn btn-sm btn-with-count tooltipped tooltipped-n"
    aria-label="You must be signed in to star a repository" rel="nofollow">
    <span class="octicon octicon-star"></span>
    Star
  </a>

    <a class="social-count js-social-count" href="/dirkgroenen/simple-jQuery-slider/stargazers">
      136
    </a>

  </li>

    <li>
      <a href="/login?return_to=%2Fdirkgroenen%2Fsimple-jQuery-slider"
        class="btn btn-sm btn-with-count tooltipped tooltipped-n"
        aria-label="You must be signed in to fork a repository" rel="nofollow">
        <span class="octicon octicon-repo-forked"></span>
        Fork
      </a>
      <a href="/dirkgroenen/simple-jQuery-slider/network" class="social-count">
        50
      </a>
    </li>
</ul>

        <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
          <span class="mega-octicon octicon-repo"></span>
          <span class="author"><a href="/dirkgroenen" class="url fn" itemprop="url" rel="author"><span itemprop="title">dirkgroenen</span></a></span><!--
       --><span class="path-divider">/</span><!--
       --><strong><a href="/dirkgroenen/simple-jQuery-slider" class="js-current-repository" data-pjax="#js-repo-pjax-container">simple-jQuery-slider</a></strong>

          <span class="page-context-loader">
            <img alt="" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
          </span>

        </h1>
      </div><!-- /.container -->
    </div><!-- /.repohead -->

    <div class="container">
      <div class="repository-with-sidebar repo-container new-discussion-timeline  ">
        <div class="repository-sidebar clearfix">
            
<nav class="sunken-menu repo-nav js-repo-nav js-sidenav-container-pjax js-octicon-loaders"
     role="navigation"
     data-pjax="#js-repo-pjax-container"
     data-issue-count-url="/dirkgroenen/simple-jQuery-slider/issues/counts">
  <ul class="sunken-menu-group">
    <li class="tooltipped tooltipped-w" aria-label="Code">
      <a href="/dirkgroenen/simple-jQuery-slider" aria-label="Code" class="selected js-selected-navigation-item sunken-menu-item" data-hotkey="g c" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /dirkgroenen/simple-jQuery-slider">
        <span class="octicon octicon-code"></span> <span class="full-word">Code</span>
        <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
</a>    </li>

      <li class="tooltipped tooltipped-w" aria-label="Issues">
        <a href="/dirkgroenen/simple-jQuery-slider/issues" aria-label="Issues" class="js-selected-navigation-item sunken-menu-item" data-hotkey="g i" data-selected-links="repo_issues repo_labels repo_milestones /dirkgroenen/simple-jQuery-slider/issues">
          <span class="octicon octicon-issue-opened"></span> <span class="full-word">Issues</span>
          <span class="js-issue-replace-counter"></span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
</a>      </li>

    <li class="tooltipped tooltipped-w" aria-label="Pull requests">
      <a href="/dirkgroenen/simple-jQuery-slider/pulls" aria-label="Pull requests" class="js-selected-navigation-item sunken-menu-item" data-hotkey="g p" data-selected-links="repo_pulls /dirkgroenen/simple-jQuery-slider/pulls">
          <span class="octicon octicon-git-pull-request"></span> <span class="full-word">Pull requests</span>
          <span class="js-pull-replace-counter"></span>
          <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
</a>    </li>

  </ul>
  <div class="sunken-menu-separator"></div>
  <ul class="sunken-menu-group">

    <li class="tooltipped tooltipped-w" aria-label="Pulse">
      <a href="/dirkgroenen/simple-jQuery-slider/pulse" aria-label="Pulse" class="js-selected-navigation-item sunken-menu-item" data-selected-links="pulse /dirkgroenen/simple-jQuery-slider/pulse">
        <span class="octicon octicon-pulse"></span> <span class="full-word">Pulse</span>
        <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
</a>    </li>

    <li class="tooltipped tooltipped-w" aria-label="Graphs">
      <a href="/dirkgroenen/simple-jQuery-slider/graphs" aria-label="Graphs" class="js-selected-navigation-item sunken-menu-item" data-selected-links="repo_graphs repo_contributors /dirkgroenen/simple-jQuery-slider/graphs">
        <span class="octicon octicon-graph"></span> <span class="full-word">Graphs</span>
        <img alt="" class="mini-loader" height="16" src="https://assets-cdn.github.com/assets/spinners/octocat-spinner-32-e513294efa576953719e4e2de888dd9cf929b7d62ed8d05f25e731d02452ab6c.gif" width="16" />
</a>    </li>
  </ul>


</nav>

              <div class="only-with-full-nav">
                  
<div class="clone-url open"
  data-protocol-type="http"
  data-url="/users/set_protocol?protocol_selector=http&amp;protocol_type=clone">
  <h3><span class="text-emphasized">HTTPS</span> clone URL</h3>
  <div class="input-group js-zeroclipboard-container">
    <input type="text" class="input-mini input-monospace js-url-field js-zeroclipboard-target"
           value="https://github.com/dirkgroenen/simple-jQuery-slider.git" readonly="readonly">
    <span class="input-group-button">
      <button aria-label="Copy to clipboard" class="js-zeroclipboard btn btn-sm zeroclipboard-button" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>

  
<div class="clone-url "
  data-protocol-type="subversion"
  data-url="/users/set_protocol?protocol_selector=subversion&amp;protocol_type=clone">
  <h3><span class="text-emphasized">Subversion</span> checkout URL</h3>
  <div class="input-group js-zeroclipboard-container">
    <input type="text" class="input-mini input-monospace js-url-field js-zeroclipboard-target"
           value="https://github.com/dirkgroenen/simple-jQuery-slider" readonly="readonly">
    <span class="input-group-button">
      <button aria-label="Copy to clipboard" class="js-zeroclipboard btn btn-sm zeroclipboard-button" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
    </span>
  </div>
</div>



<p class="clone-options">You can clone with
  <a href="#" class="js-clone-selector" data-protocol="http">HTTPS</a> or <a href="#" class="js-clone-selector" data-protocol="subversion">Subversion</a>.
  <a href="https://help.github.com/articles/which-remote-url-should-i-use" class="help tooltipped tooltipped-n" aria-label="Get help on which URL is right for you.">
    <span class="octicon octicon-question"></span>
  </a>
</p>

  <a href="https://mac.github.com" class="btn btn-sm sidebar-button" title="Save dirkgroenen/simple-jQuery-slider to your computer and use it in GitHub Desktop." aria-label="Save dirkgroenen/simple-jQuery-slider to your computer and use it in GitHub Desktop.">
    <span class="octicon octicon-device-desktop"></span>
    Clone in Desktop
  </a>


                <a href="/dirkgroenen/simple-jQuery-slider/archive/master.zip"
                   class="btn btn-sm sidebar-button"
                   aria-label="Download the contents of dirkgroenen/simple-jQuery-slider as a zip file"
                   title="Download the contents of dirkgroenen/simple-jQuery-slider as a zip file"
                   rel="nofollow">
                  <span class="octicon octicon-cloud-download"></span>
                  Download ZIP
                </a>
              </div>
        </div><!-- /.repository-sidebar -->

        <div id="js-repo-pjax-container" class="repository-content context-loader-container" data-pjax-container>
          

<a href="/dirkgroenen/simple-jQuery-slider/blob/bb794c2cb30d745d917b5e47888ecac079d9757c/src/transit.js" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:abd78b7d665f63c5a4df21e6df84eb7e -->

<div class="file-navigation js-zeroclipboard-container">
  
<div class="select-menu js-menu-container js-select-menu left">
  <span class="btn btn-sm select-menu-button js-menu-target css-truncate" data-hotkey="w"
    data-master-branch="master"
    data-ref="master"
    title="master"
    role="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <span class="octicon octicon-git-branch"></span>
    <i>branch:</i>
    <span class="js-select-button css-truncate-target">master</span>
  </span>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <span class="select-menu-title">Switch branches/tags</span>
        <span class="octicon octicon-x js-menu-close" role="button" aria-label="Close"></span>
      </div>

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" data-filter-placeholder="Filter branches/tags" class="js-select-menu-tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" data-filter-placeholder="Find a tag…" class="js-select-menu-tab">Tags</a>
            </li>
          </ul>
        </div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/dirkgroenen/simple-jQuery-slider/blob/dev/src/transit.js"
               data-name="dev"
               data-skip-pjax="true"
               rel="nofollow">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <span class="select-menu-item-text css-truncate-target" title="dev">
                dev
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open selected"
               href="/dirkgroenen/simple-jQuery-slider/blob/master/src/transit.js"
               data-name="master"
               data-skip-pjax="true"
               rel="nofollow">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <span class="select-menu-item-text css-truncate-target" title="master">
                master
              </span>
            </a>
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/v2.2.2/src/transit.js"
                 data-name="v2.2.2"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="v2.2.2">v2.2.2</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/v1.1/src/transit.js"
                 data-name="v1.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="v1.1">v1.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.3.0/src/transit.js"
                 data-name="V2.3.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.3.0">V2.3.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.2.4/src/transit.js"
                 data-name="V2.2.4"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.2.4">V2.2.4</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.2.3/src/transit.js"
                 data-name="V2.2.3"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.2.3">V2.2.3</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.2.1/src/transit.js"
                 data-name="V2.2.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.2.1">V2.2.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.2.0/src/transit.js"
                 data-name="V2.2.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.2.0">V2.2.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.0.1/src/transit.js"
                 data-name="V2.0.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.0.1">V2.0.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/V2.0/src/transit.js"
                 data-name="V2.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="V2.0">V2.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.6.2/src/transit.js"
                 data-name="2.6.2"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.6.2">2.6.2</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.6.1/src/transit.js"
                 data-name="2.6.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.6.1">2.6.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.6.0/src/transit.js"
                 data-name="2.6.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.6.0">2.6.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.5.2/src/transit.js"
                 data-name="2.5.2"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.5.2">2.5.2</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.5.1/src/transit.js"
                 data-name="2.5.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.5.1">2.5.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.5.0/src/transit.js"
                 data-name="2.5.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.5.0">2.5.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.4.2/src/transit.js"
                 data-name="2.4.2"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.4.2">2.4.2</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.4.1/src/transit.js"
                 data-name="2.4.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.4.1">2.4.1</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.4.0/src/transit.js"
                 data-name="2.4.0"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.4.0">2.4.0</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.3.5/src/transit.js"
                 data-name="2.3.5"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.3.5">2.3.5</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.3.4/src/transit.js"
                 data-name="2.3.4"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.3.4">2.3.4</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.3.2/src/transit.js"
                 data-name="2.3.2"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.3.2">2.3.2</a>
            </div>
            <div class="select-menu-item js-navigation-item ">
              <span class="select-menu-item-icon octicon octicon-check"></span>
              <a href="/dirkgroenen/simple-jQuery-slider/tree/2.3.1/src/transit.js"
                 data-name="2.3.1"
                 data-skip-pjax="true"
                 rel="nofollow"
                 class="js-navigation-open select-menu-item-text css-truncate-target"
                 title="2.3.1">2.3.1</a>
            </div>
        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div>

    </div>
  </div>
</div>

  <div class="btn-group right">
    <a href="/dirkgroenen/simple-jQuery-slider/find/master"
          class="js-show-file-finder btn btn-sm empty-icon tooltipped tooltipped-s"
          data-pjax
          data-hotkey="t"
          aria-label="Quickly jump between files">
      <span class="octicon octicon-list-unordered"></span>
    </a>
    <button aria-label="Copy file path to clipboard" class="js-zeroclipboard btn btn-sm zeroclipboard-button" data-copied-hint="Copied!" type="button"><span class="octicon octicon-clippy"></span></button>
  </div>

  <div class="breadcrumb js-zeroclipboard-target">
    <span class='repo-root js-repo-root'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/dirkgroenen/simple-jQuery-slider" class="" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">simple-jQuery-slider</span></a></span></span><span class="separator">/</span><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/dirkgroenen/simple-jQuery-slider/tree/master/src" class="" data-branch="master" data-direction="back" data-pjax="true" itemscope="url"><span itemprop="title">src</span></a></span><span class="separator">/</span><strong class="final-path">transit.js</strong>
  </div>
</div>


  <div class="commit file-history-tease">
    <div class="file-history-tease-header">
        <img alt="@dirkgroenen" class="avatar" data-user="1001391" height="24" src="https://avatars2.githubusercontent.com/u/1001391?v=3&amp;s=48" width="24" />
        <span class="author"><a href="/dirkgroenen" rel="author">dirkgroenen</a></span>
        <time datetime="2014-01-03T17:37:54Z" is="relative-time">Jan 3, 2014</time>
        <div class="commit-title">
            <a href="/dirkgroenen/simple-jQuery-slider/commit/1b77079d8b660731075d3e70f0cea83c7a267094" class="message" data-pjax="true" title="Change transition animationend boolean">Change transition animationend boolean</a>
        </div>
    </div>

    <div class="participation">
      <p class="quickstat">
        <a href="#blob_contributors_box" rel="facebox">
          <strong>1</strong>
           contributor
        </a>
      </p>
      
    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list">
          <li class="facebox-user-list-item">
            <img alt="@dirkgroenen" data-user="1001391" height="24" src="https://avatars2.githubusercontent.com/u/1001391?v=3&amp;s=48" width="24" />
            <a href="/dirkgroenen">dirkgroenen</a>
          </li>
      </ul>
    </div>
  </div>

<div class="file">
  <div class="file-header">
    <div class="file-actions">

      <div class="btn-group">
        <a href="/dirkgroenen/simple-jQuery-slider/raw/master/src/transit.js" class="btn btn-sm " id="raw-url">Raw</a>
          <a href="/dirkgroenen/simple-jQuery-slider/blame/master/src/transit.js" class="btn btn-sm js-update-url-with-hash">Blame</a>
        <a href="/dirkgroenen/simple-jQuery-slider/commits/master/src/transit.js" class="btn btn-sm " rel="nofollow">History</a>
      </div>

        <a class="octicon-btn tooltipped tooltipped-nw"
           href="https://mac.github.com"
           aria-label="Open this file in GitHub for Mac">
            <span class="octicon octicon-device-desktop"></span>
        </a>

          <button type="button" class="octicon-btn disabled tooltipped tooltipped-n" aria-label="You must be signed in to make or propose changes">
            <span class="octicon octicon-pencil"></span>
          </button>

        <button type="button" class="octicon-btn octicon-btn-danger disabled tooltipped tooltipped-n" aria-label="You must be signed in to make or propose changes">
          <span class="octicon octicon-trashcan"></span>
        </button>
    </div>

    <div class="file-info">
        10 lines (9 sloc)
        <span class="file-info-divider"></span>
      7.507 kb
    </div>
  </div>
  
  <div class="blob-wrapper data type-javascript">
      <table class="highlight tab-size-8 js-file-line-container">
      <tr>
        <td id="L1" class="blob-num js-line-number" data-line-number="1"></td>
        <td id="LC1" class="blob-code js-file-line"><span class="pl-c">/*!</span></td>
      </tr>
      <tr>
        <td id="L2" class="blob-num js-line-number" data-line-number="2"></td>
        <td id="LC2" class="blob-code js-file-line"><span class="pl-c"> * jQuery Transit - CSS3 transitions and transformations</span></td>
      </tr>
      <tr>
        <td id="L3" class="blob-num js-line-number" data-line-number="3"></td>
        <td id="LC3" class="blob-code js-file-line"><span class="pl-c"> * (c) 2011-2012 Rico Sta. Cruz &lt;rico@ricostacruz.com&gt;</span></td>
      </tr>
      <tr>
        <td id="L4" class="blob-num js-line-number" data-line-number="4"></td>
        <td id="LC4" class="blob-code js-file-line"><span class="pl-c"> * MIT Licensed.</span></td>
      </tr>
      <tr>
        <td id="L5" class="blob-num js-line-number" data-line-number="5"></td>
        <td id="LC5" class="blob-code js-file-line"><span class="pl-c"> *</span></td>
      </tr>
      <tr>
        <td id="L6" class="blob-num js-line-number" data-line-number="6"></td>
        <td id="LC6" class="blob-code js-file-line"><span class="pl-c"> * http://ricostacruz.com/jquery.transit</span></td>
      </tr>
      <tr>
        <td id="L7" class="blob-num js-line-number" data-line-number="7"></td>
        <td id="LC7" class="blob-code js-file-line"><span class="pl-c"> * http://github.com/rstacruz/jquery.transit</span></td>
      </tr>
      <tr>
        <td id="L8" class="blob-num js-line-number" data-line-number="8"></td>
        <td id="LC8" class="blob-code js-file-line"><span class="pl-c"> */</span></td>
      </tr>
      <tr>
        <td id="L9" class="blob-num js-line-number" data-line-number="9"></td>
        <td id="LC9" class="blob-code js-file-line">(function(k){k.transit={version:&quot;0.9.9&quot;,propertyMap:{marginLeft:&quot;margin&quot;,marginRight:&quot;margin&quot;,marginBottom:&quot;margin&quot;,marginTop:&quot;margin&quot;,paddingLeft:&quot;padding&quot;,paddingRight:&quot;padding&quot;,paddingBottom:&quot;padding&quot;,paddingTop:&quot;padding&quot;},enabled:true,useTransitionEnd:true};var d=document.createElement(&quot;div&quot;);var q={};function b(v){if(v in d.style){return v}var u=[&quot;Moz&quot;,&quot;Webkit&quot;,&quot;O&quot;,&quot;ms&quot;];var r=v.charAt(0).toUpperCase()+v.substr(1);if(v in d.style){return v}for(var t=0;t&lt;u.length;++t){var s=u[t]+r;if(s in d.style){return s}}}function e(){d.style[q.transform]=&quot;&quot;;d.style[q.transform]=&quot;rotateY(90deg)&quot;;return d.style[q.transform]!==&quot;&quot;}var a=navigator.userAgent.toLowerCase().indexOf(&quot;chrome&quot;)&gt;-1;q.transition=b(&quot;transition&quot;);q.transitionDelay=b(&quot;transitionDelay&quot;);q.transform=b(&quot;transform&quot;);q.transformOrigin=b(&quot;transformOrigin&quot;);q.transform3d=e();var i={transition:&quot;transitionEnd&quot;,MozTransition:&quot;transitionend&quot;,OTransition:&quot;oTransitionEnd&quot;,WebkitTransition:&quot;webkitTransitionEnd&quot;,msTransition:&quot;MSTransitionEnd&quot;};var f=q.transitionEnd=i[q.transition]||null;for(var p in q){if(q.hasOwnProperty(p)&amp;&amp;typeof k.support[p]===&quot;undefined&quot;){k.support[p]=q[p]}}d=null;k.cssEase={_default:&quot;ease&quot;,&quot;in&quot;:&quot;ease-in&quot;,out:&quot;ease-out&quot;,&quot;in-out&quot;:&quot;ease-in-out&quot;,snap:&quot;cubic-bezier(0,1,.5,1)&quot;,easeOutCubic:&quot;cubic-bezier(.215,.61,.355,1)&quot;,easeInOutCubic:&quot;cubic-bezier(.645,.045,.355,1)&quot;,easeInCirc:&quot;cubic-bezier(.6,.04,.98,.335)&quot;,easeOutCirc:&quot;cubic-bezier(.075,.82,.165,1)&quot;,easeInOutCirc:&quot;cubic-bezier(.785,.135,.15,.86)&quot;,easeInExpo:&quot;cubic-bezier(.95,.05,.795,.035)&quot;,easeOutExpo:&quot;cubic-bezier(.19,1,.22,1)&quot;,easeInOutExpo:&quot;cubic-bezier(1,0,0,1)&quot;,easeInQuad:&quot;cubic-bezier(.55,.085,.68,.53)&quot;,easeOutQuad:&quot;cubic-bezier(.25,.46,.45,.94)&quot;,easeInOutQuad:&quot;cubic-bezier(.455,.03,.515,.955)&quot;,easeInQuart:&quot;cubic-bezier(.895,.03,.685,.22)&quot;,easeOutQuart:&quot;cubic-bezier(.165,.84,.44,1)&quot;,easeInOutQuart:&quot;cubic-bezier(.77,0,.175,1)&quot;,easeInQuint:&quot;cubic-bezier(.755,.05,.855,.06)&quot;,easeOutQuint:&quot;cubic-bezier(.23,1,.32,1)&quot;,easeInOutQuint:&quot;cubic-bezier(.86,0,.07,1)&quot;,easeInSine:&quot;cubic-bezier(.47,0,.745,.715)&quot;,easeOutSine:&quot;cubic-bezier(.39,.575,.565,1)&quot;,easeInOutSine:&quot;cubic-bezier(.445,.05,.55,.95)&quot;,easeInBack:&quot;cubic-bezier(.6,-.28,.735,.045)&quot;,easeOutBack:&quot;cubic-bezier(.175, .885,.32,1.275)&quot;,easeInOutBack:&quot;cubic-bezier(.68,-.55,.265,1.55)&quot;};k.cssHooks[&quot;transit:transform&quot;]={get:function(r){return k(r).data(&quot;transform&quot;)||new j()},set:function(s,r){var t=r;if(!(t instanceof j)){t=new j(t)}if(q.transform===&quot;WebkitTransform&quot;&amp;&amp;!a){s.style[q.transform]=t.toString(true)}else{s.style[q.transform]=t.toString()}k(s).data(&quot;transform&quot;,t)}};k.cssHooks.transform={set:k.cssHooks[&quot;transit:transform&quot;].set};if(k.fn.jquery&lt;&quot;1.8&quot;){k.cssHooks.transformOrigin={get:function(r){return r.style[q.transformOrigin]},set:function(r,s){r.style[q.transformOrigin]=s}};k.cssHooks.transition={get:function(r){return r.style[q.transition]},set:function(r,s){r.style[q.transition]=s}}}n(&quot;scale&quot;);n(&quot;translate&quot;);n(&quot;rotate&quot;);n(&quot;rotateX&quot;);n(&quot;rotateY&quot;);n(&quot;rotate3d&quot;);n(&quot;perspective&quot;);n(&quot;skewX&quot;);n(&quot;skewY&quot;);n(&quot;x&quot;,true);n(&quot;y&quot;,true);function j(r){if(typeof r===&quot;string&quot;){this.parse(r)}return this}j.prototype={setFromString:function(t,s){var r=(typeof s===&quot;string&quot;)?s.split(&quot;,&quot;):(s.constructor===Array)?s:[s];r.unshift(t);j.prototype.set.apply(this,r)},set:function(s){var r=Array.prototype.slice.apply(arguments,[1]);if(this.setter[s]){this.setter[s].apply(this,r)}else{this[s]=r.join(&quot;,&quot;)}},get:function(r){if(this.getter[r]){return this.getter[r].apply(this)}else{return this[r]||0}},setter:{rotate:function(r){this.rotate=o(r,&quot;deg&quot;)},rotateX:function(r){this.rotateX=o(r,&quot;deg&quot;)},rotateY:function(r){this.rotateY=o(r,&quot;deg&quot;)},scale:function(r,s){if(s===undefined){s=r}this.scale=r+&quot;,&quot;+s},skewX:function(r){this.skewX=o(r,&quot;deg&quot;)},skewY:function(r){this.skewY=o(r,&quot;deg&quot;)},perspective:function(r){this.perspective=o(r,&quot;px&quot;)},x:function(r){this.set(&quot;translate&quot;,r,null)},y:function(r){this.set(&quot;translate&quot;,null,r)},translate:function(r,s){if(this._translateX===undefined){this._translateX=0}if(this._translateY===undefined){this._translateY=0}if(r!==null&amp;&amp;r!==undefined){this._translateX=o(r,&quot;px&quot;)}if(s!==null&amp;&amp;s!==undefined){this._translateY=o(s,&quot;px&quot;)}this.translate=this._translateX+&quot;,&quot;+this._translateY}},getter:{x:function(){return this._translateX||0},y:function(){return this._translateY||0},scale:function(){var r=(this.scale||&quot;1,1&quot;).split(&quot;,&quot;);if(r[0]){r[0]=parseFloat(r[0])}if(r[1]){r[1]=parseFloat(r[1])}return(r[0]===r[1])?r[0]:r},rotate3d:function(){var t=(this.rotate3d||&quot;0,0,0,0deg&quot;).split(&quot;,&quot;);for(var r=0;r&lt;=3;++r){if(t[r]){t[r]=parseFloat(t[r])}}if(t[3]){t[3]=o(t[3],&quot;deg&quot;)}return t}},parse:function(s){var r=this;s.replace(/([a-zA-Z0-9]+)\((.*?)\)/g,function(t,v,u){r.setFromString(v,u)})},toString:function(t){var s=[];for(var r in this){if(this.hasOwnProperty(r)){if((!q.transform3d)&amp;&amp;((r===&quot;rotateX&quot;)||(r===&quot;rotateY&quot;)||(r===&quot;perspective&quot;)||(r===&quot;transformOrigin&quot;))){continue}if(r[0]!==&quot;_&quot;){if(t&amp;&amp;(r===&quot;scale&quot;)){s.push(r+&quot;3d(&quot;+this[r]+&quot;,1)&quot;)}else{if(t&amp;&amp;(r===&quot;translate&quot;)){s.push(r+&quot;3d(&quot;+this[r]+&quot;,0)&quot;)}else{s.push(r+&quot;(&quot;+this[r]+&quot;)&quot;)}}}}}return s.join(&quot; &quot;)}};function m(s,r,t){if(r===true){s.queue(t)}else{if(r){s.queue(r,t)}else{t()}}}function h(s){var r=[];k.each(s,function(t){t=k.camelCase(t);t=k.transit.propertyMap[t]||k.cssProps[t]||t;t=c(t);if(k.inArray(t,r)===-1){r.push(t)}});return r}function g(s,v,x,r){var t=h(s);if(k.cssEase[x]){x=k.cssEase[x]}var w=&quot;&quot;+l(v)+&quot; &quot;+x;if(parseInt(r,10)&gt;0){w+=&quot; &quot;+l(r)}var u=[];k.each(t,function(z,y){u.push(y+&quot; &quot;+w)});return u.join(&quot;, &quot;)}k.fn.transition=k.fn.transit=function(z,s,y,C){var D=this;var u=0;var w=true;if(typeof s===&quot;function&quot;){C=s;s=undefined}if(typeof y===&quot;function&quot;){C=y;y=undefined}if(typeof z.easing!==&quot;undefined&quot;){y=z.easing;delete z.easing}if(typeof z.duration!==&quot;undefined&quot;){s=z.duration;delete z.duration}if(typeof z.complete!==&quot;undefined&quot;){C=z.complete;delete z.complete}if(typeof z.queue!==&quot;undefined&quot;){w=z.queue;delete z.queue}if(typeof z.delay!==&quot;undefined&quot;){u=z.delay;delete z.delay}if(typeof s===&quot;undefined&quot;){s=k.fx.speeds._default}if(typeof y===&quot;undefined&quot;){y=k.cssEase._default}s=l(s);var E=g(z,s,y,u);var B=k.transit.enabled&amp;&amp;q.transition;var t=B?(parseInt(s,10)+parseInt(u,10)):0;if(t===0){var A=function(F){D.css(z);if(C){C.apply(D)}if(F){F()}};m(D,w,A);return D}var x={};var r=function(H){var G=false;var F=function(){if(G){D.unbind(f,F)}if(t&gt;0){D.each(function(){this.style[q.transition]=(x[this]||null)})}if(typeof C===&quot;function&quot;){C.apply(D)}if(typeof H===&quot;function&quot;){H()}};if((t&gt;0)&amp;&amp;(f)&amp;&amp;(k.transit.useTransitionEnd)){G=true;D.bind(f,F)}else{window.setTimeout(F,t)}D.each(function(){if(t&gt;0){this.style[q.transition]=E}k(this).css(z)})};var v=function(F){this.offsetWidth;r(F)};m(D,w,v);return this};function n(s,r){if(!r){k.cssNumber[s]=true}k.transit.propertyMap[s]=q.transform;k.cssHooks[s]={get:function(v){var u=k(v).css(&quot;transit:transform&quot;);return u.get(s)},set:function(v,w){var u=k(v).css(&quot;transit:transform&quot;);u.setFromString(s,w);k(v).css({&quot;transit:transform&quot;:u})}}}function c(r){return r.replace(/([A-Z])/g,function(s){return&quot;-&quot;+s.toLowerCase()})}function o(s,r){if((typeof s===&quot;string&quot;)&amp;&amp;(!s.match(/^[\-0-9\.]+$/))){return s}else{return&quot;&quot;+s+r}}function l(s){var r=s;if(k.fx.speeds[r]){r=k.fx.speeds[r]}return o(r,&quot;ms&quot;)}k.transit.getTransitionValue=g})(jQuery);</td>
      </tr>
</table>

  </div>

</div>

<a href="#jump-to-line" rel="facebox[.linejump]" data-hotkey="l" style="display:none">Jump to Line</a>
<div id="jump-to-line" style="display:none">
  <form accept-charset="UTF-8" action="" class="js-jump-to-line-form" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" autofocus>
    <button type="submit" class="btn">Go</button>
</form></div>

        </div>

      </div><!-- /.repo-container -->
      <div class="modal-backdrop"></div>
    </div><!-- /.container -->
  </div><!-- /.site -->


    </div><!-- /.wrapper -->

      <div class="container">
  <div class="site-footer" role="contentinfo">
    <ul class="site-footer-links right">
        <li><a href="https://status.github.com/" data-ga-click="Footer, go to status, text:status">Status</a></li>
      <li><a href="https://developer.github.com" data-ga-click="Footer, go to api, text:api">API</a></li>
      <li><a href="https://training.github.com" data-ga-click="Footer, go to training, text:training">Training</a></li>
      <li><a href="https://shop.github.com" data-ga-click="Footer, go to shop, text:shop">Shop</a></li>
        <li><a href="https://github.com/blog" data-ga-click="Footer, go to blog, text:blog">Blog</a></li>
        <li><a href="https://github.com/about" data-ga-click="Footer, go to about, text:about">About</a></li>

    </ul>

    <a href="https://github.com" aria-label="Homepage">
      <span class="mega-octicon octicon-mark-github" title="GitHub"></span>
</a>
    <ul class="site-footer-links">
      <li>&copy; 2015 <span title="0.03845s from github-fe125-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="https://github.com/site/terms" data-ga-click="Footer, go to terms, text:terms">Terms</a></li>
        <li><a href="https://github.com/site/privacy" data-ga-click="Footer, go to privacy, text:privacy">Privacy</a></li>
        <li><a href="https://github.com/security" data-ga-click="Footer, go to security, text:security">Security</a></li>
        <li><a href="https://github.com/contact" data-ga-click="Footer, go to contact, text:contact">Contact</a></li>
    </ul>
  </div>
</div>


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-suggester-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="fullscreen-contents js-fullscreen-contents" placeholder=""></textarea>
      <div class="suggester-container">
        <div class="suggester fullscreen-suggester js-suggester js-navigation-container"></div>
      </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped tooltipped-w" aria-label="Exit Zen Mode">
      <span class="mega-octicon octicon-screen-normal"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped tooltipped-w"
      aria-label="Switch themes">
      <span class="octicon octicon-color-mode"></span>
    </a>
  </div>
</div>



    
    

    <div id="ajax-error-message" class="flash flash-error">
      <span class="octicon octicon-alert"></span>
      <a href="#" class="octicon octicon-x flash-close js-ajax-error-dismiss" aria-label="Dismiss error"></a>
      Something went wrong with that request. Please try again.
    </div>


      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/frameworks-d22b59d0085e83b7549ba4341ec9e68f80c2f29c8e49213ee182003dc8d568c6.js"></script>
      <script async="async" crossorigin="anonymous" src="https://assets-cdn.github.com/assets/github-d869f6edeea2dbd9c7c3595e2f31cf8a1530bd36eaa84707461f65c5ee848853.js"></script>
      
      

  </body>
</html>

