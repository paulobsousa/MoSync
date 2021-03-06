/*
 * Copyright 2007 Doxological Ltd.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tokenizer_states.h"
#include "char_classes.h"

FAXPP_Error
comment_start_state1(FAXPP_TokenizerEnv *env)
{
  read_char(env);

  switch(env->current_char) {
  case '-':
    env->state = comment_start_state2;
    next_char(env);
    break;
  case 'D':
    env->state = comment_content_state;
    token_start_position(env);
    next_char(env);
    return DOCTYPE_NOT_IMPLEMENTED;
  LINE_ENDINGS
  default:
    env->state = comment_content_state;
    token_start_position(env);
    next_char(env);
    return INVALID_START_OF_COMMENT;
  }
  return NO_ERROR;
}

FAXPP_Error
comment_start_state2(FAXPP_TokenizerEnv *env)
{
  read_char(env);

  switch(env->current_char) {
  case '-':
    env->state = comment_content_state;
    next_char(env);
    token_start_position(env);
    break;
  LINE_ENDINGS
  default:
    env->state = comment_content_state;
    token_start_position(env);
    next_char(env);
    return INVALID_START_OF_COMMENT;
  }
  return NO_ERROR;
}

FAXPP_Error
comment_content_state(FAXPP_TokenizerEnv *env)
{
  while(1) {
    read_char(env);

    switch(env->current_char) {
    case '-':
      env->state = comment_content_seen_dash_state;
      env->token_position1 = env->token_buffer.cursor ? env->token_buffer.cursor : env->position;
      next_char(env);
      return NO_ERROR;
    LINE_ENDINGS
      break;
    default:
      if((FAXPP_char_flags(env->current_char) & env->non_restricted_char) == 0) {
        next_char(env);
        return RESTRICTED_CHAR;
      }
      break;
    }

    next_char(env);
  }

  // Never happens
  return NO_ERROR;
}

FAXPP_Error
comment_content_seen_dash_state(FAXPP_TokenizerEnv *env)
{
  read_char(env);

  switch(env->current_char) {
  case '-':
    env->state = comment_content_seen_dash_twice_state;
    env->token_position2 = env->token_position1;
    env->token_position1 = env->token_buffer.cursor ? env->token_buffer.cursor : env->position;
    break;
  LINE_ENDINGS
    env->state = comment_content_state;
    break;
  default:
    env->state = comment_content_state;
    return NO_ERROR;
  }

  next_char(env);
  return NO_ERROR;
}

FAXPP_Error
comment_content_seen_dash_twice_state(FAXPP_TokenizerEnv *env)
{
  read_char(env);

  switch(env->current_char) {
  case '>':
    base_state(env);
    env->token_buffer.cursor = 0;
    env->token.value.len = env->token_position2 - env->token.value.ptr;
    report_token(COMMENT_TOKEN, env);
    next_char(env);
    token_start_position(env);
    break;
  case '-':
    env->token_position2 = env->token_position1;
    env->token_position1 = env->token_buffer.cursor ? env->token_buffer.cursor : env->position;
    next_char(env);
    return DOUBLE_DASH_IN_COMMENT;
  LINE_ENDINGS
  default:
    env->state = comment_content_state;
    return DOUBLE_DASH_IN_COMMENT;
  }
  return NO_ERROR;
}

